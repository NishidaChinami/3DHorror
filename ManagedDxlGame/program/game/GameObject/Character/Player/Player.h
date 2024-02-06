#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject.h"

class GameCamera;
class Mediator;
class StageWall;
class Flashlight;
class Sound;

//-------------------------------------------------------------------------------------------------//
//プレイヤークラス
// ユーザーが操作する
//-------------------------------------------------------------------------------------------------//

class Player : public GameObject
{
public:
	Player() {};
	//描画用のカメラクラスとオブジェクトの参照先をもつメディエータークラスを引数にもつ
	Player(std::shared_ptr<GameCamera>gamecamera, const std::shared_ptr<Mediator>&mediator);
	~Player();
	//更新処理
	void Update(float delta_time)override;
	//描画処理
	void Draw(std::shared_ptr<GameCamera>gamecamera) override {}
	//死んだときの関数
	void GameoverEvent();
	//ステージと当たったときの処理
	void StageCorrection(const std::shared_ptr<StageWall>& stagewall);

	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(tnl::Vector3, PlayerPos, mesh->pos_);
	tnl::Quaternion getPlayerRot()const{ return mesh->rot_; }
	tnl::Vector3 getPlayerSize() const { return size; }
	float getPlayerSpeed()const { return m_speed; }
	float getPlayerStamina() const { return m_stamina; }
	bool getPlayerDash()const { return m_can_dash; }

	static const int MAXSTAMINA = 1200;
private:
	//プレイヤーの移動状態を管理するシークエンス
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqWalk);
	//各移動状態
	bool seqWalk(const float delta_time);	//歩き移動
	bool seqRun(const float delta_time);	//走り移動
	bool seqSneek(const float delta_time);	//しゃがみ移動
	bool seqDeath(const float delta_time);	//死亡処理
	
	// プレイヤーの移動速度
	float m_speed = 0;
	//一フレーム前の位置
	tnl::Vector3 m_prev_pos;
	//走るときのスタミナ
	int m_stamina = 0;
	//走れるかどうかのフラグ
	bool m_can_dash = true;

	//足音をチュートリアルとメインゲームで切り替えるための変数
	std::string m_walk_sound;
	std::string m_run_sound;


	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Flashlight>m_flashlight = nullptr;
	std::shared_ptr<GameCamera>m_gamecamera = nullptr;
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//----------------------定数------------------------//
	//走る速度
	const float DASH_SPEED = 10;
	//歩く速度
	const float WALK_SPEED = 4;
	//しゃがみ速度
	const float WALK_SNEEK = 2;
	//疲労状態のスタミナ数値
	const float TIREDNESS = 10;
	
};

