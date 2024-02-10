#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"
class Inventory;
class Message;
class Factory;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//サブシーンクラス
// タイトルやプレイ画面のクラスの子クラスとして機能
// インベントリーやチュートリアルの説明などUIの表示を担当
//-------------------------------------------------------------------------------------------------//

class SubScene : public BaseScene
{
public:
	SubScene() {};
	//プレイやチュートリアルで使うオブジェクトの情報をもつFactoryクラスとMediatorクラスを引数に持つ
	SubScene(std::shared_ptr<Factory>factory, std::shared_ptr<Mediator>mediator);
	~SubScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;

	//チュートリアルで表示する情報をもつ
	struct TutorialDate
	{
		std::string s_mess; //チュートリアルの説明文
		eKeys s_key;        //入力待ちするキー
		bool s_light_flug;  //懐中電灯を持っているかどうか
	};
	//チュートリアル表示のコルーチン
	TNL_CO_SEQUENCE(SubScene, &SubScene::seqIdle);

	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(bool, BoolInventory, m_active_inventory);
	TNL_PROPERTY(bool, BoolEvent, m_active_event);
	TNL_PROPERTY(bool, BoolTutorial, m_active_tutorial);

private:
	//シーン遷移用のテンプレート
	tnl::Sequence<SubScene> sequence_ = tnl::Sequence<SubScene>(this, &SubScene::seqIdle);
	//結果画面またはスタート画面に戻る
	bool seqIdle(float delta_time);
	bool seqTutorialUI(float delta_time);
	bool seqEventUI(float delta_time);
	bool seqInventoryUI(float delta_time);

	//各UIの表示のフラグ
	bool m_active_inventory = false;
	bool m_active_event = false;
	bool m_active_tutorial = true;

	//フェードアウト用変数
	int m_alpha = 0;
	float m_time_count = 0;

	//チュートリアルで表示する文字の変数
	std::string m_tutorial_message;
	//チュートリアルデータを保存するベクター
	std::vector<TutorialDate>m_tutorial_date;

	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Factory>m_factory;
	std::shared_ptr<Mediator>m_mediator;
	//----------------------定数------------------------//
	//イベントUI発生時の背景画面のサイズ
	const float EVENTUI_WIGHT = 800;
	const float EVENTUI_HEIGHT = 600;
	//各文字の座標
	const tnl::Vector3 TUTORIAL_MESSEAGE = { 640,500,0 };
	const tnl::Vector3 DASHGAUGE_POS = { 640,620,0 };
	//体力ゲージの高さ
	const float GAUGE_HEIGHT = 5;
	//文字のサイズ
	const int TUTORIAL_FONT = 20;
	const int EVENT_FONT = 18;
	const int INVENTORY_FONT = 20;

};

