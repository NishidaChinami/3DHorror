#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseUI.h"
#include"Message.h"

class GameCamera;
class Inventory;
class Message;

class MainUI :public BaseUI
{
public:
	MainUI();
	~MainUI(){}
	void Draw()override {}
	void Update(float delta_time)override;
	TNL_CO_SEQUENCE(MainUI, &MainUI::seqTutorialUI);

	//eventUIを呼び出すフラグ
	void SetEvnetNotify(bool notice, int title);
	
	std::shared_ptr<Inventory>GetClassInventory() { return m_inventory; }
	std::shared_ptr<Message>GetClassMessage() { return m_message; }
private:
	//シーン遷移用のテンプレート
	tnl::Sequence<MainUI> sequence_ = tnl::Sequence<MainUI>(this, &MainUI::seqIdle);
	//結果画面またはスタート画面に戻る
	bool seqIdle(float delta_time);

	//bool seqPlayMainUI(float delta_time);
	bool seqTutorialUI(float delta_time);
	bool seqSettingUI(float delta_time);
	bool seqEventUI(float delta_time);
	bool seqInventoryUI(float delta_time);

	//文章のデータクラスポインタ
	std::shared_ptr<Message>m_message = nullptr;
	//インベントリー
	std::shared_ptr<Inventory>m_inventory = nullptr;

	bool m_return_title = false;

	bool m_event_notify = false;

	const float EVENTUI_WIGHT = 800;
	const float EVENTUI_HEIGHT = 600;
};

