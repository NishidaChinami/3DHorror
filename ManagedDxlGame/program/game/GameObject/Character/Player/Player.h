#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject.h"

class GameCamera;
class Mediator;
class StageWall;
class Flashlight;
class Sound;

/// <summary>
/// ユーザーが操作するプレイヤークラス
/// </summary>

class Player : public GameObject
{
public:
	Player() {};
	Player(std::shared_ptr<Sound>sound, std::shared_ptr<GameCamera>gamecamera);
	~Player();

	void Update(float delta_time)override;
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	//死んだときの関数
	void Death() {};
	//ステージと当たったときの関数
	void StageCorrection(const std::shared_ptr<StageWall>& stagewall);

	tnl::Vector3 GetPlayerPos()const { return mesh->pos_; }
	void SetPlayerPos(tnl::Vector3& pos) { mesh->pos_; }
	tnl::Quaternion GetPlayerRot() { return mesh->rot_; }
	tnl::Vector3 GetPlayerSize() const { return size; }
	float GetPlayerSpeed()const { return m_speed; }
	float GetPlayerStamina() const { return m_stamina; }

private:
	//プレイヤーの移動状態を管理するシークエンス
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqWalk);
	//各移動状態
	bool seqWalk(const float delta_time);
	bool seqRun(const float delta_time);
	bool seqEvent(const float delta_time);
	bool seqSneek(const float delta_time);
	//bool seqHide(const float delta_time);
	// 
	// プレイヤーの移動速度
	float m_speed = 0;
	//走る速度
	const float m_dash_speed = 10;
	//歩く速度
	const float m_walk_speed = 3;
	//一フレーム前の位置
	tnl::Vector3 m_prev_pos;
	//走るときのスタミナ
	int m_stamina = 1000;
	bool m_can_dash = true;
	//サウンドを管理するブール
	bool m_play_sound = false;
	bool m_switch_sound = false;

	//懐中電灯のポインタ
	std::shared_ptr<Flashlight>m_flashlight = nullptr;
	//サインドのポインタ
	std::shared_ptr<Sound>m_sound = nullptr;
	std::shared_ptr<GameCamera>m_player_camera = nullptr;

	
	
	
};

