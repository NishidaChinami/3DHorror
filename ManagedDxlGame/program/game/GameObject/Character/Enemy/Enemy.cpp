#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../Mylibrary/Conversion.h"
#include"Enemy.h"
#include"../../Camera/GameCamera.h"
#include"../../../Manager/Mediator.h"
#include"../../../Effect/Sound/Sound.h"


Enemy::Enemy(tnl::Vector3 pos, const std::shared_ptr<Mediator>&mediator)
{
	//最短経路の計算クラス生成
	path = std::make_shared<astar::Path>();
	//modelの初期設定
	m_model_enemy = MV1LoadModel("model/zombi.mv1");
	m_texture_enmey = LoadGraph("texture/T_Human_mutant_3_Albedo.PNG");
	MV1SetScale(m_model_enemy, VGet(3, 3, 3));
	MV1SetTextureGraphHandle(m_model_enemy, 0, m_texture_enmey, FALSE);
	MV1SetMaterialEmiColor(m_model_enemy,0, GetColorF(0.8f, 0.5f, 0.4f, 1.0f));

	//当たり判定用にMeshも用意
	mesh = dxe::Mesh::CreateSphereMV(30);
	mesh->pos_ = pos;
	size = { 400,400,400 };
	//メディエーターが使えるようにコンストラクタでメディエーターのアドレスを受け取る
	if (mediator)m_mediator = mediator;
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_model_enemy);
	DeleteGraph(m_texture_enmey);
	Sound::GetInstance()->SoundStop("ENEMYAPPROACHING");
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void Enemy::Update(float delta_time) {
	m_prev_pos = mesh->pos_;
	auto sound = Sound::GetInstance();
	sound->Sound3DUpdate(m_mediator->MGetPlayerPos(), tnl::Quaternion{ 0,0,1,0 }, mesh->pos_, "ENEMYAPPROACHING", HEAR_RANGE);
	if (!sound->SoundPlaying("ENEMYAPPROACHING"))sound->SoundPlay("ENEMYAPPROACHING");
	sequence_.Update(delta_time);
	
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void Enemy::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//MV1modelのポジションを設定
	//VECTOR pos_vec = VGet(mesh->pos_.x, mesh->pos_.y, mesh->pos_.z);
	MV1SetPosition(m_model_enemy, cf::ConvertToV3(mesh->pos_));
	//modelの描画
	MV1DrawModel(m_model_enemy);
	//if (!tnl::IsIntersectSphere(mesh->pos_, size.x, tnl::Vector3(2500, 0, 2500), 3000))DrawStringEx(100, 100, -1, "脱走");
}

//------------------------------------------------------------------------------------------------------------
//視野に入っているかどうか
bool Enemy::WithinView() {
	//プレイヤーとEnemyの視野角のRayの当たり判定をとるために左奥上座標と右前下座標を取得
	tnl::Vector3 aabb_max = { m_mediator->MGetPlayerPos() + tnl::Vector3(-m_mediator->MGetPlayerSize().x / 2,m_mediator->MGetPlayerSize().y / 2,m_mediator->MGetPlayerSize().z / 2) };
	tnl::Vector3 aabb_min = { m_mediator->MGetPlayerPos() + tnl::Vector3(m_mediator->MGetPlayerSize().x / 2,-m_mediator->MGetPlayerSize().y / 2,-m_mediator->MGetPlayerSize().z / 2) };
	
	//すべてのRayと当たり判定を求める
	float fov = DX_PI_F / 2;
	float angle = 0;
	//体の向きを取得し正面のベクトルを求める
	tnl::Vector3 vision = mesh->rot_.getEuler();
	float center = vision.y;
	//正面からπ/4だけ範囲をとる
	float left = center - fov / 2;
	float right = center + fov / 2;

	//扇形のRayを作成　これを視野角とする
	for (angle = left; angle < right; angle += fov / 10) {
		tnl::Vector3 ray = { sin(angle), 0, cos(angle) };
		ray.normalize();
		//プレイヤーにあたっているか判定
		if (!IsIntersectRayAABB(mesh->pos_, ray, aabb_max, aabb_min))continue;
		ray *= 6000;
		//ブレセンハムでRayが通るマップのステート情報を取得
		std::vector<tnl::Vector2i> ray_intersection;
		ray_intersection = GetBresenhamsLine(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), cf::GridPos(mesh->pos_ + ray, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE));
		int index = 0;
		//ブレセンハムで取得したステートが、壁がさきだったらだったら偽を返し、プレイヤーの場合真を返す
		while (index < ray_intersection.size()) {
			if (m_mediator->MGetStageState(ray_intersection[index].y, ray_intersection[index].x) == maze::StageState::Wall) break;
			else if (cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE) == ray_intersection[index]) {
				return true;
			}
			index++;
		}
		ray_intersection.clear();
	}
	return false;

	
}
//------------------------------------------------------------------------------------------------------------
//聴覚　音が聞こえるかどうか
bool Enemy::Hearing() {
	auto sound = Sound::GetInstance();
	//Enemyから一定の範囲のところで走ると聞こえた判定になる
	if (tnl::IsIntersectSphere(mesh->pos_, HEARED_RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x)) {
		if (sound->SoundPlaying("RUN"))return true;
	}
	else return false;
}

//void Enemy::StageCorrection(const std::shared_ptr<StageWall>& stagewall) {

	/*tnl::CorrectPositionAABB(
		m_prev_pos
		, stagewall->GetStageWallPos()
		, size
		, tnl::Vector3(StageWall::BLOCKSIZE, StageWall::BLOCKHIGHT, StageWall::BLOCKSIZE)
		, mesh->pos_
		, stagewall->mesh->pos_
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B, 0.1f);*/

//}


//------------------------------------------------------------------------------------------------------------
//回転移動
bool Enemy::seqRotate(const float delta_time) {
	//次の向きを計算
	tnl::Quaternion target_rot = tnl::Quaternion::LookAtAxisY(mesh->pos_, m_next_target);
	//ゆっくり回転させる
	mesh->rot_.slerp(target_rot, sequence_.getProgressTime());
	if (sequence_.getProgressFrame() >= 1.0f) {
		//最終的に位置を調整
		mesh->rot_ = target_rot;
		//MV1model用の回転関数に代入できるようDxlib Vector型に変換
		tnl::Vector3 e_rot = mesh->rot_.getEuler();
		MV1SetRotationXYZ(m_model_enemy, { TNL_DEP_V3(e_rot) });
		//移動シーケンスに移行
		sequence_.change(&Enemy::seqMovement);
	}
	return true;
};
//------------------------------------------------------------------------------------------------------------
//移動
bool Enemy::seqMovement(const float delta_time) {
	//移動からポイントの更新へ
	tnl::Vector3 target = m_next_target - mesh->pos_;
	//到達したら更新シーケンスへ
	if (fabs(target.x) < FLT_EPSILON && fabs(target.z) < FLT_EPSILON) {
		sequence_.change(&Enemy::seqUpdatePoint);
		return true;
	};
	//Enemyの向いている向きに移動させる
	mesh->pos_+= tnl::Vector3::TransformCoord({ 0,0,m_speed }, mesh->rot_);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//目的地のアップデート
bool Enemy::seqUpdatePoint(const float delta_time) {
	m_index--;

	if (WithinView()) {
		sequence_.change(&Enemy::seqTrack); 
		chase_state = true;
		return true;
	}
	if (Hearing()) {
		sequence_.change(&Enemy::seqTrack); 
		chase_state = true;
		return true;
	}
	if (m_index < 0) {
		if (chase_state)sequence_.change(&Enemy::seqTrack);
		else sequence_.change(&Enemy::seqPatrol);
		if (!WithinView() && !Hearing())chase_state = false;
		return true;
	}
	m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
	sequence_.change(&Enemy::seqRotate);
	return true;
}
//------------------------------------------------------------------------------------------------------------
//追尾状態の最短経路探索
bool Enemy::seqTrack(const float delta_time) {
//プレイヤーを終点として最短経路を求める
	m_speed = CHASE_SPEED;
	route.clear();
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		&route, 
		Stage::STAGE_ROW, 
		Stage::STAGE_COL);
	m_index = route.size()-1;
	if (m_index <= 0)return true;
	m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
	sequence_.change(&Enemy::seqRotate);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//巡回　ランダムなアイテムの最短経路
bool Enemy::seqPatrol(const float delta_time) {
	m_speed = PATROL_SPEED;
	route.clear();
	int random = rand() % 5;
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		m_mediator->MGetItemPos()[random],
		&route, 
		Stage::STAGE_ROW, 
		Stage::STAGE_COL);
		m_index = route.size()-2;
		if (m_index <= 0)return true;
		m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
		sequence_.change(&Enemy::seqRotate);
	return true;
};

//------------------------------------------------------------------------------------------------------------
//最短経路計算処理
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
	astar::Node* first_row[Stage::STAGE_ROW];
	for (int i = 0; i < Stage::STAGE_ROW; ++i) {
		first_row[i] = nodes[i];
	}

	// 経路探索実行
	bool is_success = path->Aster(first_row, &nodes[start.y][start.x], _route, row, col);

	
}
//------------------------------------------------------------------------------------------------------------
//ゲームオーバーの関数呼び出し
void Enemy::GameoverEvent()
{
	MV1SetMaterialEmiColor(m_model_enemy, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	sequence_.change(&Enemy::seqPlayerDeath);
}
//------------------------------------------------------------------------------------------------------------
//ゲームオーバー状態
bool Enemy::seqPlayerDeath(const float delta_time)
{
	tnl::Quaternion target_rot;
	target_rot = tnl::Quaternion::LookAtAxisY(mesh->pos_, m_mediator->MGetPlayerPos());
	mesh->rot_ = target_rot;
	tnl::Vector3 e_rot = mesh->rot_.getEuler();
	MV1SetRotationXYZ(m_model_enemy, { TNL_DEP_V3(e_rot) });
	//プレイヤーの前に立つ
	mesh->pos_ = tnl::Vector3( m_mediator->MGetPlayerPos().x,200,m_mediator->MGetPlayerPos().y ) + tnl::Vector3::TransformCoord({ 0,0,50 }, m_mediator->MGetPlayerRot());
	return true;
}