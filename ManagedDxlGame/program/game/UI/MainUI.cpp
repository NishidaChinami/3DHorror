#include "../dxlib_ext/dxlib_ext.h"
#include"MainUI.h"
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"

MainUI::MainUI(){
	m_inventory = std::make_shared<Inventory>();
	m_message = std::make_shared<Message>();
}

void MainUI::Update(float delta_time) {
	sequence_.Update(delta_time);
}

bool MainUI::seqIdle(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))sequence_.change(&MainUI::seqSettingUI);
	if(m_event_notify)sequence_.change(&MainUI::seqEventUI);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))sequence_.change(&MainUI::seqInventoryUI);
	return true;
}
//勝手に一回呼び出し
bool MainUI::seqTutorialUI(float delta_time) {
	//コルーチン用
	while (1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			DrawStringEx(100, 100, -1, "WASDキーで移動" );
				if(tnl::Input::IsKeyDown(eKeys::KB_W) ||
					tnl::Input::IsKeyDown(eKeys::KB_S) ||
					tnl::Input::IsKeyDown(eKeys::KB_A) ||
					tnl::Input::IsKeyDown(eKeys::KB_D) )TNL_SEQ_CO_BREAK;
		});
		
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			DrawStringEx(100, 100, -1, "Ctrlでしゃがみ");
			if(tnl::Input::IsKeyDown(eKeys::KB_LCONTROL))TNL_SEQ_CO_BREAK;
		});
	}
	//ライトをGetしたかどうか
	//if (bool getlight) {
	//	//TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
	//		//DrawStringEx(100,100,-1,"%s",)
	//		//if (tnl::Input::IsKeyDown(eKeys::KB_TAB))TNL_SEQ_CO_BREAK;
	//		//});

	//	TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
	//		//DrawStringEx(100,100,-1,"%s",)
	//		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))TNL_SEQ_CO_BREAK;
	//	});

	//	TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {});
	//	//トリガーとなる当たり判定を設けるか時間で管理するか
	//	sequence_.change(&MainUI::seqIdle);
	//}

	TNL_SEQ_CO_END;
	return true;
}

//Escapeを押されたら呼び出し、インベンとリーもTaｂ呼ばれたら呼び出し
bool MainUI::seqSettingUI(float delta_time) {
	//入力はマウスで移動距離を測定し、それにそった値に変化
	// バーの数値実際の音量の数値に設定
	//スタートへ戻るでブール値変化
	DrawStringEx(200, 299, -1, "設定画面");
	//シート２は
	//操作説明
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))sequence_.change(&MainUI::seqIdle);
	return true;
}

bool MainUI::seqEventUI(float delta_time) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//itemからの通知により、描画
	if (tnl::Input::IsMouseDown(eMouse::LEFT))sequence_.change(&MainUI::seqIdle);
	return true;
}

bool MainUI::seqInventoryUI(float delta_time) {
	m_inventory->Draw();
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))sequence_.change(&MainUI::seqIdle);
	return true;
}

//eventUIを呼び出すフラグ（Messageもここでいいかな）
//itemとかで呼び出し
void MainUI::SetEvnetNotify(bool notice, int title) {
	m_event_notify = notice;
	m_message->ChangeStory(title);

}