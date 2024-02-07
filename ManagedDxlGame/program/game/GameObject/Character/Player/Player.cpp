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
	//見えないメッシュを生成
	mesh = dxe::Mesh::CreateCubeMV(50);
	texture = dxe::Texture::CreateFromFile("graphics/box.bmp");
	mesh->setTexture(texture);
	//当たり判定の大きさを設定
	size = { 100,600,200 };
	m_mediator = mediator;
	//懐中電灯の生成
	m_flashlight = std::make_shared<Flashlight>();
	//カメラを参照して、回転と座標をプレイヤーにも入れる
	m_gamecamera = gamecamera;
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//スタミナの初期化
	m_stamina = MAXSTAMINA;
}

Player::~Player()
{
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void Player::Update(float delta_time) {
	//一フレーム前の座標を保存
	m_prev_pos = mesh->pos_;
	//懐中電灯が有効になったら更新を入れる
	if(m_mediator->MGetLightParam())m_flashlight->Update(mesh->pos_, m_gamecamera->getCameraRot());
	//チュートリアルとメインゲームで足音を変える
	GameManager::GetInstance()->is_tutorial == true ? (m_walk_sound = { "GROUNDWALK" }, m_run_sound = { "GROUNDRUN" }) : (m_walk_sound = { "WALK" }, m_run_sound = { "RUN" });
	sequence_.Update(delta_time);

}
//------------------------------------------------------------------------------------------------------------
//死んだときの関数
void Player::GameoverEvent()
{
	sequence_.change(&Player::seqDeath);
}
//------------------------------------------------------------------------------------------------------------
//ステージと当たったときの処理
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
//歩き状態のシーケンス
bool Player::seqWalk(const float delta_time) {

	//速度を歩くに設定
	m_speed = WALK_SPEED;
	//カメラから移動と回転を取得
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();

	//スタミナ管理
	if (m_stamina < MAXSTAMINA) m_stamina += 2;
	if (m_stamina >= MAXSTAMINA/2)m_can_dash = true;

	//サウンド再生と停止
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
	//シーケンスの切り替え処理
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);
	if(m_can_dash &&tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))sequence_.change(&Player::seqRun);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//走り状態のシーケンス
bool Player::seqRun(const float delta_time) {
	//速度を走る設定
	m_speed = DASH_SPEED;
	//スタミナの減少
	m_stamina -= 2;
	//カメラから移動と回転を取得
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//スタミナが一定値以下になると歩き状態へ
	if (m_stamina <= TIREDNESS) {
		m_can_dash = false;
		sequence_.change(&Player::seqWalk);
	}
	
	//サウンド再生と停止
	auto sound = Sound::GetInstance();
	sound->SoundStop(m_walk_sound.c_str());
	sound->Sound3DUpdate(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), mesh->pos_- tnl::Vector3(0,200,0), "RUN");
	sound->Sound3DUpdate(mesh->pos_, tnl::Quaternion(0, 0, 1, 0), mesh->pos_ - tnl::Vector3(0, 200, 0), "BREATHLESSNESS");
	if (!sound->SoundPlaying(m_run_sound.c_str())) sound->SoundPlay(m_run_sound.c_str());
	if(m_can_dash)sound->SoundPlay("BREATHLESSNESS");
	//シーケンスの切り替え処理
	if (!tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) sequence_.change(&Player::seqWalk);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqSneek);

	return true;
}

//------------------------------------------------------------------------------------------------------------
//しゃがみ状態のシーケンス
bool Player::seqSneek(const float delta_time) {
	//速度をしゃがみ設定
	m_speed = WALK_SNEEK;
	//頭の高さを変更
	if (mesh->pos_.y >= 200) {
		mesh->pos_.y -= 10;
		m_gamecamera->pos_ = mesh->pos_;
	}
	//カメラから移動と回転を取得
	mesh->pos_ = m_gamecamera->pos_;
	mesh->rot_ = m_gamecamera->getCameraRot();
	//しゃがみから歩きに切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) sequence_.change(&Player::seqWalk);
	return true;
}

//------------------------------------------------------------------------------------------------------------
//死んだときのシーケンス
bool Player::seqDeath(const float delta_time)
{	//視点をEnemy方向へ
	m_gamecamera->setCameraRot(tnl::Quaternion::LookAt(mesh->pos_, m_mediator->MGetEnemyPos(), { 0,1,0 }));
	//カメラ振動をさせる
	m_gamecamera->CameraVibration();
	return true;
}


