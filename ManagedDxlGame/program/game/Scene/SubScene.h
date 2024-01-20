#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"
class Inventory;
class Message;
class Factory;
class Mediator;

class SubScene : public BaseScene
{
public:
	SubScene() {};
	//SubScene(std::shared_ptr<Inventory>inventory,std::shared_ptr<Message>message):m_inventory(inventory),m_message(message){}
	SubScene(std::shared_ptr<Factory>factory, std::shared_ptr<Mediator>mediator) :m_factory(factory), m_mediator(mediator) {}
	~SubScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;

	//eventUIを呼び出すフラグ
	//void SetEvnetNotify(bool notice, int title);

	TNL_CO_SEQUENCE(SubScene, &SubScene::seqIdle);

	void SetBoolInventory(bool active) { active_inventory = active; }
	void SetBoolEvent(bool active) { active_event = active; }
	void SetBoolOption(bool active) { active_option = active; }


private:
	//シーン遷移用のテンプレート
	tnl::Sequence<SubScene> sequence_ = tnl::Sequence<SubScene>(this, &SubScene::seqTutorialUI);
	//結果画面またはスタート画面に戻る
	bool seqIdle(float delta_time);
	bool seqTutorialUI(float delta_time);
	bool seqSettingUI(float delta_time);
	bool seqEventUI(float delta_time);
	bool seqInventoryUI(float delta_time);

	//ファクトリークラス
	std::shared_ptr<Factory>m_factory;
	std::shared_ptr<Mediator>m_mediator;

	const float EVENTUI_WIGHT = 800;
	const float EVENTUI_HEIGHT = 600;

	bool active_inventory = false;
	bool active_option = false;
	bool active_event = false;
	bool active_tutorial = true;

	std::string m_tutorial_message;

	const tnl::Vector3 TUTORIAL_MESSEAGE = { 640,600,0 };
	const tnl::Vector3 DASHGAUGE_POS = { 640,620,0 };
	const float GAUGE_HEIGHT = 5;
};

