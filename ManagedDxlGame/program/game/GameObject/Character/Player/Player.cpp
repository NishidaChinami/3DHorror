#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../Player/Player.h"
#include"../../Camera/GameCamera.h"
#include"../../../Manager/Mediator.h"
#include"../../Stage/Stage.h"
#include"../../Stage/StageParts.h"
#include"../../Item/Flashlight.h"
#include"../../../Effect/Sound/Sound.h"

Player::Player(std::shared_ptr<Sound>sound, std::shared_ptr<GameCamera>gamecamera)
{
	mesh = dxe::Mesh::CreateCubeMV(50);
	texture = dxe::Texture::CreateFromFile("graphics/box.bmp");
	mesh->setTexture(texture);
	size = { 100,400,100 };
	m_flashlight = std::make_shared<Flashlight>();
	m_sound = sound;
	m_player_camera = gamecamera;
	mesh->pos_ = m_player_camera->pos_;
	mesh->rot_ = m_player_camera->GetCameraRot();
}

Player::~Player()
{
}

void Player::Update(float delta_time) {
	m_prev_pos = mesh->pos_;
	sequence_.Update(delta_time);
	m_flashlight->Update(mesh->pos_, m_player_camera->GetCameraRot());
	
}

void Player::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//mesh->render(gamecamera);
	
}


void Player::StageCorrection(const std::shared_ptr<StageWall>&stagewall) {

	tnl::CorrectPositionAABB(
		m_player_camera->GetPrevPos()
		, stagewall->GetStageWallPos()
		, size
		, tnl::Vector3(StageWall::BLOCKSIZE,StageWall::BLOCKHIGHT,StageWall::BLOCKSIZE)
		, m_player_camera->pos_
		, stagewall->mesh->pos_
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B
		, tnl::eCorrTypeAABB::PWRFL_B, 0.1f);
	
}

bool Player::seqWalk(const float delta_time) {
	m_sound->SoundStop("RUN");
	//スタミナ管理
	if (m_stamina < 1000) m_stamina++;
	if (m_stamina >= 500) {
		m_can_dash = true;
		m_sound->SoundStop("BREATHLESSNESS");
	}
	//速度を歩くに設定
	m_speed = m_walk_speed;
	

	mesh->pos_ = m_player_camera->pos_;
	mesh->rot_ = m_player_camera->GetCameraRot();
	m_sound->Sound3DPlay(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), (mesh->pos_ - tnl::Vector3(0, size.y / 2, 0)), "WALK");
	
	if(!m_sound->SoundPlaying("WALK"))m_sound->SoundPlay("WALK");
	
	if (!tnl::Input::IsKeyDown(eKeys::KB_D) &&
		!tnl::Input::IsKeyDown(eKeys::KB_A) &&
		!tnl::Input::IsKeyDown(eKeys::KB_W) &&
		!tnl::Input::IsKeyDown(eKeys::KB_S)) {
		
		m_sound->SoundStop("WALK");
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);
	if(m_can_dash &&tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))sequence_.change(&Player::seqRun);
	return true;
}

bool Player::seqRun(const float delta_time) {
	m_speed = m_dash_speed;
	m_stamina -= 2;
	m_sound->SoundStop("WALK");
	mesh->pos_ = m_player_camera->pos_;
	mesh->rot_ = m_player_camera->GetCameraRot();
	if (m_stamina <= 10) {
		m_can_dash = false;
		m_sound->SoundPlay("BREATHLESSNESS");
		sequence_.change(&Player::seqWalk);
	}
	
	
	m_sound->Sound3DPlay(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), (mesh->pos_ - tnl::Vector3(0, size.y / 2, 0)), "RUN");
	m_sound->Sound3DPlay(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), (mesh->pos_ - tnl::Vector3(0, size.y / 2, 0)), "BREATHLESSNESS");
	if (!m_sound->SoundPlaying("RUN")) m_sound->SoundPlay("RUN");
	
	if (!tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) sequence_.change(&Player::seqWalk);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);

	return true;
}


bool Player::seqSneek(const float delta_time) {
	static tnl::Vector3 pos = mesh->pos_;
	if (mesh->pos_.y >= pos.y / 2) {
		mesh->pos_.y -= 2;
		m_player_camera->pos_.y = mesh->pos_.y;
	}
	mesh->pos_ = m_player_camera->pos_;
	mesh->rot_ = m_player_camera->GetCameraRot();
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) {
		m_player_camera->pos_.y = 200;
		sequence_.change(&Player::seqWalk);
	}
	return true;
}

bool Player::seqEvent(const float delta_time) { return true; }

