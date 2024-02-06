#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


class Factory;
class Collision;
class Player;
class Enemy;
class StageWall;
class MainUI;
class SubScene;
class OptionScene;
class Sound;

//-------------------------------------------------------------------------------------------------//
// メインプレイ画面のクラス
//-------------------------------------------------------------------------------------------------//
class PlayScene final : public BaseScene, public std::enable_shared_from_this<PlayScene> {
public:

	PlayScene();
	~PlayScene()override;
	//更新処理
	void Update(float delta_time)override;
	//描画処理
	void Draw()override;
	//BGM再生関数
	void PlayBGM();
	//当たり判定を取る準備を行う関数
	void CollisionFuc();

	//子クラスの追加
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}

private:
	//シーン状態のシーケンス
	tnl::Sequence<PlayScene> sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::seqMainGame);
	bool seqMainGame(float delta_time);					//ゲームのプレイ状態
	bool seqOpenUI(float delta_time);					//UIを開いているときの状態
	//bool seqIdle(float delta_time) { return true; }		//待機状態

	//ゲームオーバー時の血のグラフィックハンドル
	int m_gameover_gpc_hdl = 0;

	//親クラスのリスト
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//子クラスのポインタ
	std::shared_ptr<SubScene>m_subscene;
	std::shared_ptr<OptionScene>m_option;
	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Factory>m_factory = nullptr;
	std::shared_ptr<Collision>m_collision = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<StageWall>> m_stagewall;

	//bool m_alive_tutorial = false;
};