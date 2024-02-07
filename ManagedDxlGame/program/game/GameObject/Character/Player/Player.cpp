#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../../../Manager/Mediator.h"
#include"../../../Manager/Manager.h"
//-------------------GameObject file------------------------//
#include"../Player/Player.h"
#include"../../Camera/GameCamera.h"
#include"../../Stage/Stage.h"
#include"../../Stage/StageParts.h"
#include"../../Item/Flashlight.h"
//-------------------Effect file------------------------//
#include"../../../Effect/Sound/Sound.h"

Player::Player(std::shared_ptr<GameCamera>gamecamera, const std::shared_ptr<Mediator>&mediator)
{
	//�����Ȃ����b�V���𐶐�
	mesh = dxe::Mesh::CreateCubeMV(50);
	texture = dxe::Texture::CreateFromFile("graphics/box.bmp");
	mesh->setTexture(texture);
	//�����蔻��̑傫����ݒ�
	size = { 100,600,200 };
	m_mediator = mediator;
	//�����d���̐���
	m_flashlight = std::make_shared<Flashlight>();
	//�J�������Q�Ƃ��āA��]�ƍ��W���v���C���[�ɂ������
	m_gamecamera = gamecamera;
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//�X�^�~�i�̏�����
	m_stamina = MAXSTAMINA;
}

Player::~Player()
{
}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void Player::Update(float delta_time) {
	//��t���[���O�̍��W��ۑ�
	m_prev_pos = mesh->pos_;
	//�����d�����L���ɂȂ�����X�V������
	if(m_mediator->MGetLightParam())m_flashlight->Update(mesh->pos_, m_gamecamera->getCameraRot());
	//�`���[�g���A���ƃ��C���Q�[���ő�����ς���
	GameManager::GetInstance()->is_tutorial == true ? (m_walk_sound = { "GROUNDWALK" }, m_run_sound = { "GROUNDRUN" }) : (m_walk_sound = { "WALK" }, m_run_sound = { "RUN" });
	sequence_.Update(delta_time);

}
//------------------------------------------------------------------------------------------------------------
//���񂾂Ƃ��̊֐�
void Player::GameoverEvent()
{
	sequence_.change(&Player::seqDeath);
}
//------------------------------------------------------------------------------------------------------------
//�X�e�[�W�Ɠ��������Ƃ��̏���
void Player::StageCorrection(const std::shared_ptr<StageWall>&stagewall) {

	tnl::CorrectPositionAABB(
		m_gamecamera->getPrevPos()
		, stagewall->GetStageWallPos()
		, size
		, tnl::Vector3(StageWall::BLOCKSIZE,StageWall::BLOCKHIGHT,StageWall::BLOCKSIZE)
		, m_gamecamera->pos_
		, stagewall->mesh->pos_
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B, 0.1f);
	
}

//------------------------------------------------------------------------------------------------------------
//������Ԃ̃V�[�P���X
bool Player::seqWalk(const float delta_time) {

	//���x������ɐݒ�
	m_speed = WALK_SPEED;
	//�J��������ړ��Ɖ�]���擾
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();

	//�X�^�~�i�Ǘ�
	if (m_stamina < MAXSTAMINA) m_stamina += 2;
	if (m_stamina >= MAXSTAMINA/2)m_can_dash = true;

	//�T�E���h�Đ��ƒ�~
	auto sound = Sound::GetInstance();
	sound->SoundStop(m_run_sound.c_str());
	sound->Sound3DUpdate(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), (mesh->pos_ - tnl::Vector3(0, 200, 0)), "WALK");
	if (!sound->SoundPlaying(m_walk_sound.c_str()))sound->SoundPlay(m_walk_sound.c_str());
	if(m_can_dash)sound->SoundStop("BREATHLESSNESS");
	
	if (!tnl::Input::IsKeyDown(eKeys::KB_D) &&
		!tnl::Input::IsKeyDown(eKeys::KB_A) &&
		!tnl::Input::IsKeyDown(eKeys::KB_W) &&
		!tnl::Input::IsKeyDown(eKeys::KB_S)) {
		
		sound->SoundStop(m_walk_sound.c_str());
	}
	//�V�[�P���X�̐؂�ւ�����
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);
	if(m_can_dash &&tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))sequence_.change(&Player::seqRun);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//�����Ԃ̃V�[�P���X
bool Player::seqRun(const float delta_time) {
	//���x�𑖂�ݒ�
	m_speed = DASH_SPEED;
	//�X�^�~�i�̌���
	m_stamina -= 2;
	//�J��������ړ��Ɖ�]���擾
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//�X�^�~�i�����l�ȉ��ɂȂ�ƕ�����Ԃ�
	if (m_stamina <= TIREDNESS) {
		m_can_dash = false;
		sequence_.change(&Player::seqWalk);
	}
	
	//�T�E���h�Đ��ƒ�~
	auto sound = Sound::GetInstance();
	sound->SoundStop(m_walk_sound.c_str());
	sound->Sound3DUpdate(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), mesh->pos_- tnl::Vector3(0,200,0), "RUN");
	sound->Sound3DUpdate(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), mesh->pos_ - tnl::Vector3(0, 200, 0), "BREATHLESSNESS");
	if (!sound->SoundPlaying(m_run_sound.c_str())) sound->SoundPlay(m_run_sound.c_str());
	if(m_can_dash)sound->SoundPlay("BREATHLESSNESS");
	//�V�[�P���X�̐؂�ւ�����
	if (!tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) sequence_.change(&Player::seqWalk);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);

	return true;
}

//------------------------------------------------------------------------------------------------------------
//���Ⴊ�ݏ�Ԃ̃V�[�P���X
bool Player::seqSneek(const float delta_time) {
	//���x�����Ⴊ�ݐݒ�
	m_speed = WALK_SNEEK;
	//���̍�����ύX
	if (mesh->pos_.y >= 200) {
		mesh->pos_.y -= 10;
		m_gamecamera->pos_ = mesh->pos_;
	}
	//�J��������ړ��Ɖ�]���擾
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//���Ⴊ�݂�������ɐ؂�ւ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqWalk);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//���񂾂Ƃ��̃V�[�P���X
bool Player::seqDeath(const float delta_time)
{	//���_��Enemy������
	m_gamecamera->setCameraRot(tnl::Quaternion::LookAt(mesh->pos_, m_mediator->MGetEnemyPos(), { 0,1,0 }));
	//�J�����U����������
	m_gamecamera->CameraVibration();
	return true;
}


