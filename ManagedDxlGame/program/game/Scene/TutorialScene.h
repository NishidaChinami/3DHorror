#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class Factory;
class Collision;
class Player;
class StageWall;
class SubScene;
class OptionScene;
class GameParticle;
//-------------------------------------------------------------------------------------------------//
// チュートリアルステージのクラス
//-------------------------------------------------------------------------------------------------//
class TutorialScene : public BaseScene
{
public:
	TutorialScene();
	~TutorialScene();
	//更新処理
	void Update(float delta_time)override;
	//描画処理
	void Draw()override;
	//当たり判定を取る準備を行う関数
	void CollisionFunc();

	//子クラスの追加
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}

private:
	//シーン状態のシーケンス
	tnl::Sequence<TutorialScene> sequence_ = tnl::Sequence<TutorialScene>(this, &TutorialScene::seqMainGame);
	bool seqMainGame(float delta_time);	//ゲームのプレイ状態
	bool seqOpenUI(float delta_time);	//UIを開いているときの状態

	//親クラスのリストを用意
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//子クラスのポインタ
	std::shared_ptr<SubScene>m_subscene;
	std::shared_ptr<OptionScene>m_option;
	//シャドウマップポインタ
	Shared<dxe::ShadowMap> m_shadow = nullptr;
	//パーティクルポインタ
	Shared<GameParticle>particle = nullptr;

	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Collision>collision = nullptr;
	std::shared_ptr<Factory>m_factory = nullptr;
	std::shared_ptr<Collision>m_collision = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::list<std::shared_ptr<StageWall>> m_stagewall;
	//--------------定数--------------------------//
	const int FONT_SIZE = 18;
};
