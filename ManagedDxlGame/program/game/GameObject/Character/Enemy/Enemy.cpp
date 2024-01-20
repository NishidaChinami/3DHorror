#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../Mylibrary/Conversion.h"
#include"Enemy.h"
#include"../../Camera/GameCamera.h"
#include"../../../Manager/Mediator.h"
#include"../../../Effect/Sound/Sound.h"


Enemy::Enemy(tnl::Vector3 pos, const std::shared_ptr<Mediator>mediator,std::shared_ptr<Sound>sound)
{
	path = std::make_shared<astar::Path>();
	
	m_model_enemy = MV1LoadModel("model/enemy.mv1");
	MV1SetScale(m_model_enemy, VGet(2, 2, 2));
	MV1SetOpacityRate(m_model_enemy, 0.8f);
	MV1SetEmiColorScale(m_model_enemy, GetColorF(0.8f, 1.0f, 1.0f, 1.0f));
	MV1SetAmbColorScale(m_model_enemy, GetColorF(0.5f, 1.0f, 0.5f, 1.0f));
	MV1SetDifColorScale(m_model_enemy, GetColorF(1.0f, 0.6f, 0.5f, 1.0f));
	
	mesh = dxe::Mesh::CreateSphereMV(30);
	mesh->pos_ = pos;
	size = { 30,30,30 };
	if (mediator)m_mediator = mediator;
	if (sound)m_sound = sound;
}

Enemy::~Enemy()
{
	DeleteGraph(m_model_enemy);
	DeleteGraph(m_texture_enmey);
}

void Enemy::Update(float delta_time) {
	m_sound->Sound3DPlay(m_mediator->MGetPlayerPos(), tnl::Quaternion{ 0,0,1,0 }, mesh->pos_, "ENEMYAPPROACHING", 1000);
	if (!m_sound->SoundPlaying("ENEMYAPPROACHING"))m_sound->SoundPlay("ENEMYAPPROACHING");
	sequence_.Update(delta_time);
	if (WithinView()) {
		if (!chase_state) {
			sequence_.change(&Enemy::seqTrack);
			chase_state = true;
		}
		debug = true;
	}
	if (Hearing()) {
		if (!can_hear) {
			sequence_.change(&Enemy::seqTrack);
			can_hear = true;
		}
	}
	else { debug = false; }
}
void Enemy::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//mesh->render(gamecamera);
	CreatRay(gamecamera);
	VECTOR pos_vec = VGet(mesh->pos_.x, mesh->pos_.y, mesh->pos_.z);
	MV1SetPosition(m_model_enemy, pos_vec);
	MV1DrawModel(m_model_enemy);
	if (debug == true)DrawStringEx(100, 100, -1, "見える");
}


void Enemy::CreatRay(std::shared_ptr<GameCamera>gamecamera) {
	//弧状のレイを作成
	float fov = DX_PI_F / 2;
	float angle = 0;
	tnl::Vector3 siya = mesh->rot_.getEuler();
	float center = siya.y;
	float left = center - fov / 2;
	float right = center + fov / 2;
	
	for (angle = left; angle < right; angle += fov/10) {
		ray =(sin(angle)*6000, 0,cos(angle)*6000);
		//デバック用
		DrawLine3DEx(gamecamera, mesh->pos_, tnl::Vector3(sin(angle)*500, 0, cos(angle)*500) + mesh->pos_, -1);
	}
}

bool Enemy::WithinView() {
	tnl::Vector3 aabb_max = { m_mediator->MGetPlayerPos() + tnl::Vector3(-m_mediator->MGetPlayerSize().x / 2,m_mediator->MGetPlayerSize().y / 2,m_mediator->MGetPlayerSize().z / 2) };
	tnl::Vector3 aabb_min = { m_mediator->MGetPlayerPos() + tnl::Vector3(m_mediator->MGetPlayerSize().x / 2,-m_mediator->MGetPlayerSize().y / 2,-m_mediator->MGetPlayerSize().z / 2) };
	
	//すべてのRayと当たり判定を求める
	float fov = DX_PI_F / 2;
	float angle = 0;
	tnl::Vector3 siya = mesh->rot_.getEuler();
	float center = siya.y;
	float left = center - fov / 2;
	float right = center + fov / 2;

	for (angle = left; angle < right; angle += fov / 10) {
		ray = { sin(angle), 0, cos(angle) };
		ray.normalize();
		if (!IsIntersectRayAABB(mesh->pos_, ray, aabb_max, aabb_min))continue;
		ray *= 6000;
		std::vector<tnl::Vector2i> ray_intersection;
		ray_intersection = GetBresenhamsLine(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), cf::GridPos(mesh->pos_ + ray, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE));
		int index = 0;
		while (index < ray_intersection.size()) {
			if (m_mediator->MGetStageState(ray_intersection[index].y, ray_intersection[index].x) == maze::StageState::Wall) break;
			else if (cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE) == ray_intersection[index]) return true;
			index++;
		}
		ray_intersection.clear();
	}
	return false;

	
}

bool Enemy::Hearing() {
	if (tnl::IsIntersectSphere(mesh->pos_, RADIUS_RUN, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x)) {
		if (m_sound->SoundPlaying("RUN"))return true;
	}
	else if (tnl::IsIntersectSphere(mesh->pos_, RADIUS_WALK, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x)) {
		if (m_sound->SoundPlaying("WALK"))return true;
	}
	else return false;
}


bool Enemy::seqRotate(const float delta_time) {

	//次の向き
	tnl::Quaternion target_rot;
	target_rot = tnl::Quaternion::LookAtAxisY(mesh->pos_, m_next_target);
	//mesh->rot_.slerp(target_rot, delta_time * 10);
	mesh->rot_ = target_rot;
	tnl::Vector3 e_rot = mesh->rot_.getEuler();
	VECTOR Debug = { TNL_DEP_V3(e_rot) };
	MV1SetRotationXYZ(m_model_enemy, Debug);
	sequence_.change(&Enemy::seqMovement);

	return true;
};
bool Enemy::seqMovement(const float delta_time) {
	
	//移動からポイントの更新へ
	tnl::Vector3 target;
	
	target = m_next_target - mesh->pos_;
	if (fabs(target.x) < FLT_EPSILON && fabs(target.z) < FLT_EPSILON) {
		//ここが通ってない
		sequence_.change(&Enemy::seqUpdatePoint);
		return true;
	};
	//mesh->pos_+= tnl::Vector3::TransformCoord({ 0,0,m_speed }, mesh->rot_);
	return true;
}

bool Enemy::seqUpdatePoint(const float delta_time) {

	m_index--;
	if (m_index < 0) {
		if (chase_state)sequence_.change(&Enemy::seqTrack);
		else sequence_.change(&Enemy::seqPatrol);
		if (!Hearing())can_hear = false;
		return true;
	}
	m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
	sequence_.change(&Enemy::seqRotate);
	return true;
}

bool Enemy::seqTrack(const float delta_time) {
//プレイヤーを終点として最短経路を求める
	if (chase_state)m_speed = CHASE_SPEED;
	else m_speed = PATROL_SPEED;

	route.clear();
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		&route, 
		Stage::m_row, 
		Stage::m_col);
	m_index = route.size()-1;

	//見えなくても一回再度経路探索する
	if(WithinView() == false)chase_state = false;
	sequence_.change(&Enemy::seqUpdatePoint);

	return true;
};
bool Enemy::seqPatrol(const float delta_time) {
	m_speed = PATROL_SPEED;
	route.clear();
	int random = rand() % 5;
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		m_mediator->MGetItemPos()[random],
		&route, 
		Stage::m_row, 
		Stage::m_col);
		m_index = route.size()-1;
		sequence_.change(&Enemy::seqUpdatePoint);

	return true;
};


void Enemy::Routing(tnl::Vector2i start, tnl::Vector2i end, std::vector < astar:: Node* > * _route, int row, int col)
{

	// ノードデータの初期設定
	for (int i = 0; i < row; ++i) {
		for (int k = 0; k < col; ++k) {
			nodes[i][k].pos = tnl::Vector2i(k, i);
			if (m_mediator->MGetStageState(i, k) != maze::StageState::Wall) {
				nodes[i][k].status = astar::TrackState::ROAD;
			}
			nodes[i][k].cost_guess = abs(end.x - k) + abs(end.y - i);
		}
	}
	nodes[start.y][start.x].status = astar::TrackState::START;
	nodes[end.y][end.x].status = astar::TrackState::END;
	nodes[start.y][start.x].parent = nullptr;

	// 二次元配列のアドレスを引数に渡す為の準備
	astar::Node* first_row[Stage::m_row];
	for (int i = 0; i < Stage::m_row; ++i) {
		first_row[i] = nodes[i];
	}

	// 経路探索実行
	bool is_success = path->Aster(first_row, &nodes[start.y][start.x], _route, row, col);

	
}

