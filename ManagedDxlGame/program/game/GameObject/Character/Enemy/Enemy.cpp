#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../../../Manager/Mediator.h"
//-------------------GameObject file------------------------//
#include"Enemy.h"
#include"../../Camera/GameCamera.h"
//-------------------Effect file------------------------//
#include"../../../Effect/Sound/Sound.h"


Enemy::Enemy(tnl::Vector3 pos, const std::shared_ptr<Mediator>&mediator)
{
	//�ŒZ�o�H�̌v�Z�N���X����
	path = std::make_shared<astar::Path>();
	//model�̏����ݒ�
	m_model_enemy = MV1LoadModel("model/zombi.mv1");
	m_texture_enmey = LoadGraph("texture/T_Human_mutant_3_Albedo.PNG");
	MV1SetScale(m_model_enemy, VGet(3, 3, 3));
	MV1SetTextureGraphHandle(m_model_enemy, 0, m_texture_enmey, FALSE);
	MV1SetMaterialEmiColor(m_model_enemy,0, GetColorF(0.8f, 0.5f, 0.4f, 1.0f));

	//�����蔻��p��Mesh���p��
	mesh = dxe::Mesh::CreateSphereMV(30);
	mesh->pos_ = pos;
	size = { 400,400,400 };
	//���f�B�G�[�^�[���g����悤�ɃR���X�g���N�^�Ń��f�B�G�[�^�[�̃A�h���X���󂯎��
	if (mediator) { m_mediator = mediator; }
	m_intersect_pos = new tnl::Vector3();
}

Enemy::~Enemy()
{
	Sound::GetInstance()->SoundStop("ENEMYAPPROACHING");
	MV1DeleteModel(m_model_enemy);
	DeleteGraph(m_texture_enmey);
	delete m_intersect_pos;
}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void Enemy::Update(float delta_time) {
	m_prev_pos = mesh->pos_;
	auto sound = Sound::GetInstance();
	sound->Sound3DUpdate(m_mediator->MGetPlayerPos(), tnl::Quaternion{ 0,0,1,0 }, mesh->pos_, "ENEMYAPPROACHING", HEAR_RANGE);
	if (!sound->SoundPlaying("ENEMYAPPROACHING")) {
		sound->SoundPlay("ENEMYAPPROACHING");
	}
	sequence_.Update(delta_time);
}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void Enemy::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//MV1model�̃|�W�V������ݒ�
	MV1SetPosition(m_model_enemy, cf::ConvertToV3(mesh->pos_));
	//model�̕`��
	MV1DrawModel(m_model_enemy);
}

//------------------------------------------------------------------------------------------------------------
//����ɓ����Ă��邩�ǂ���
bool Enemy::WithinSight() {
	//�v���C���[��Enemy�̎���p��Ray�̓����蔻����Ƃ邽�߂ɍ�������W�ƉE�O�����W���擾
	tnl::Vector3 aabb_max = { tnl::Vector3(m_mediator->MGetPlayerPos().x,GameCamera::HEAD_HEIGHT,m_mediator->MGetPlayerPos().z)
		+ tnl::Vector3(-m_mediator->MGetPlayerSize().x / 2,m_mediator->MGetPlayerSize().y / 2,m_mediator->MGetPlayerSize().z / 2) };
	tnl::Vector3 aabb_min = { tnl::Vector3(m_mediator->MGetPlayerPos().x,GameCamera::HEAD_HEIGHT,m_mediator->MGetPlayerPos().z)
		+ tnl::Vector3(m_mediator->MGetPlayerSize().x / 2,-m_mediator->MGetPlayerSize().y / 2,-m_mediator->MGetPlayerSize().z / 2) };
	
	//���ׂĂ�Ray�Ɠ����蔻������߂�
	float fov = DX_PI_F / 2;
	float angle = 0;
	//�̂̌������擾�����ʂ̃x�N�g�������߂�
	tnl::Vector3 vision = mesh->rot_.getEuler();
	float center = vision.y;
	//���ʂ����/4�����͈͂��Ƃ�
	float left = center - fov;
	float right = center + fov;

	if ((m_mediator->MGetPlayerPos() - mesh->pos_).length() > HEAR_RANGE) { return false; }
	//��`��Ray���쐬�@���������p�Ƃ���
	for (angle = left; angle < right; angle += fov / 15) {
		tnl::Vector3 ray = { sin(angle), 0, cos(angle) };
		ray.normalize();
		//�v���C���[�ɂ������Ă��邩����
		if (!tnl::IsIntersectRayAABB(mesh->pos_, ray, aabb_max, aabb_min, m_intersect_pos)) { continue; }
		//�ǂ���O��
		if (m_mediator->MGetIntersectStage(mesh->pos_, ray, m_intersect_pos)) { return true; }
	}
	return false;

	
}
//------------------------------------------------------------------------------------------------------------
//���o�@�����������邩�ǂ���
bool Enemy::Hearing() {
	auto sound = Sound::GetInstance();
	//Enemy������͈̔͂̂Ƃ���ő���ƕ�����������ɂȂ�
	if (tnl::IsIntersectSphere(mesh->pos_, RUN_RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x)) {
		if (sound->SoundPlaying("RUN")) { return true; }
	}
	else if (tnl::IsIntersectSphere(mesh->pos_, WALK_RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x)) {
		if (sound->SoundPlaying("WALK")) { return true; }
	}
	else return false;
}


//------------------------------------------------------------------------------------------------------------
//��]�ړ�
bool Enemy::seqRotate(const float delta_time) {
	//���̌������v�Z
	tnl::Quaternion target_rot = tnl::Quaternion::LookAtAxisY(mesh->pos_, m_next_target);
	//��������]������
	mesh->rot_.slerp(target_rot, sequence_.getProgressTime());
	if (sequence_.getProgressFrame() >= 1.0f) {
		//�ŏI�I�Ɉʒu�𒲐�
		mesh->rot_ = target_rot;
		//MV1model�p�̉�]�֐��ɑ���ł���悤Dxlib Vector�^�ɕϊ�
		tnl::Vector3 e_rot = mesh->rot_.getEuler();
		MV1SetRotationXYZ(m_model_enemy, { TNL_DEP_V3(e_rot) });
		//�ړ��V�[�P���X�Ɉڍs
		sequence_.change(&Enemy::seqMovement);
	}
	return true;
};
//------------------------------------------------------------------------------------------------------------
//�ړ�
bool Enemy::seqMovement(const float delta_time) {
	//�ړ�����|�C���g�̍X�V��
	tnl::Vector3 target = m_next_target - mesh->pos_;
	//���B������X�V�V�[�P���X��
	if (fabs(target.x) < FLT_EPSILON && fabs(target.z) < FLT_EPSILON) {
		sequence_.change(&Enemy::seqUpdatePoint);
		return true;
	};
	//Enemy�̌����Ă�������Ɉړ�������
	mesh->pos_+= tnl::Vector3::TransformCoord({ 0,0,m_speed }, mesh->rot_);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//�ړI�n�̃A�b�v�f�[�g
bool Enemy::seqUpdatePoint(const float delta_time) {
	m_index--;
	if (!chase_state) {
		//����ɓ�������
		if (WithinSight()) {
			sequence_.change(&Enemy::seqTrack);
			chase_state = true;
			return true;
		}
		//����������������
		if (Hearing()) {
			sequence_.change(&Enemy::seqTrack);
			chase_state = true;
			return true;
		}
	}
	//���[�g�̃C���f�b�N�X���O�ɂȂ�����ŒZ�o�H�g�݂Ȃ���
	if (m_index < 0) {
		if (chase_state) { sequence_.change(&Enemy::seqTrack); }
		else { sequence_.change(&Enemy::seqPatrol); }
		//����ƒ��o�ŔF���ł��Ȃ��ꍇ
		if (!WithinSight() && !Hearing()) {
			chase_state = false;
		}
		return true;
	}
	//���̒n�_��o�^
	m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
	//��]���
	sequence_.change(&Enemy::seqRotate);
	return true;
}
//------------------------------------------------------------------------------------------------------------
//�ǔ���Ԃ̍ŒZ�o�H�T��
bool Enemy::seqTrack(const float delta_time) {
//�v���C���[���I�_�Ƃ��čŒZ�o�H�����߂�
	m_speed = CHASE_SPEED;
	route.clear();
	//�v���C���[�Ƃ̍ŒZ�o�H�𒲂ׂ�
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		&route, 
		Stage::STAGE_ROW, 
		Stage::STAGE_COL);
	m_index = route.size()-1;
	if (m_index <= 0) { return true; }
	//�ŏ��̖ړI�n��o�^
	m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
	//��]���
	sequence_.change(&Enemy::seqRotate);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//����@�����_���ȃA�C�e���̍ŒZ�o�H
bool Enemy::seqPatrol(const float delta_time) {
	m_speed = PATROL_SPEED;
	route.clear();
	int random = rand() % 5;
	//�����_���ɃA�C�e����I��ōŒZ�o�H�𒲂ׂ�
	Routing(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),
		m_mediator->MGetItemPos()[random],
		&route, 
		Stage::STAGE_ROW, 
		Stage::STAGE_COL);
		m_index = route.size()-2;
		if (m_index <= 0) { return true; }
		//�ŏ��̖ړI�n��o�^
		m_next_target = cf::Coordinate(route[m_index]->pos, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE);
		//��]���
		sequence_.change(&Enemy::seqRotate);
	return true;
};

//------------------------------------------------------------------------------------------------------------
//�ŒZ�o�H�v�Z����
void Enemy::Routing(tnl::Vector2i start, tnl::Vector2i end, std::vector < astar:: Node* > * _route, int row, int col)
{

	// �m�[�h�f�[�^�̏����ݒ�
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

	// �񎟌��z��̃A�h���X�������ɓn���ׂ̏���
	astar::Node* first_row[Stage::STAGE_ROW];
	for (int i = 0; i < Stage::STAGE_ROW; ++i) {
		first_row[i] = nodes[i];
	}

	// �o�H�T�����s
	bool is_success = path->Aster(first_row, &nodes[start.y][start.x], _route, row, col);

	
}
//------------------------------------------------------------------------------------------------------------
//�Q�[���I�[�o�[�̊֐��Ăяo��
void Enemy::GameoverEvent()
{
	MV1SetMaterialEmiColor(m_model_enemy, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	sequence_.change(&Enemy::seqPlayerDeath);
}
//------------------------------------------------------------------------------------------------------------
//�Q�[���I�[�o�[���
bool Enemy::seqPlayerDeath(const float delta_time)
{
	tnl::Quaternion target_rot;
	target_rot = tnl::Quaternion::LookAtAxisY(mesh->pos_, m_mediator->MGetPlayerPos());
	mesh->rot_ = target_rot;
	tnl::Vector3 e_rot = mesh->rot_.getEuler();
	MV1SetRotationXYZ(m_model_enemy, { TNL_DEP_V3(e_rot) });
	//�v���C���[�̑O�ɗ���
	mesh->pos_ = tnl::Vector3( m_mediator->MGetPlayerPos().x,200,m_mediator->MGetPlayerPos().y ) + tnl::Vector3::TransformCoord({ 0,0,50 }, m_mediator->MGetPlayerRot());
	return true;
}

//ray *= 8000;
////�u���Z���n����Ray���ʂ�}�b�v�̃X�e�[�g�����擾
//std::vector<tnl::Vector2i> ray_intersection;
//ray_intersection = GetBresenhamsLine(cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), cf::GridPos(mesh->pos_ + ray, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE));
//int index = 0;
////�u���Z���n���Ŏ擾�����X�e�[�g���A�ǂ������������炾������U��Ԃ��A�v���C���[�̏ꍇ�^��Ԃ�
//while (index < ray_intersection.size()) {
//	if (m_mediator->MGetStageState(ray_intersection[index].y, ray_intersection[index].x) == maze::StageState::Wall) break;
//	else if (cf::GridPos(m_mediator->MGetPlayerPos(), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE) == ray_intersection[index]) {
//		return true;
//	}
//	index++;
//}
//ray_intersection.clear();