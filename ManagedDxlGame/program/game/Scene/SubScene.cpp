#include "../dxlib_ext/dxlib_ext.h"
#include"SubScene.h"
#include"../Mylibrary/Conversion.h"
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"

SubScene::~SubScene()
{
}

void SubScene::Update(float delta_time) {
	sequence_.Update(delta_time);
}

void SubScene::Draw() {
	if (active_event) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		m_factory->GetClassMessage()->MessageDraw();
	}
	else if(active_inventory)m_factory->GetClassInventory()->Draw();
	else if (active_option) {
		DrawStringEx(200, 299, -1, "設定画面");
	}
	else {
		DrawStringEx(640, 360, -1, "+");
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {
			DrawBoxEx(DASHGAUGE_POS, m_mediator->MGetPlayerStamina(), GAUGE_HEIGHT, true, -1);
		}
	}
	//チュートリアル中の文字の描画
	if (active_tutorial) {
		cf::DrawCenterString(m_tutorial_message.c_str(),TUTORIAL_MESSEAGE);
	}
}

bool SubScene::seqIdle(float delta_time) {
	if (active_option)sequence_.change(&SubScene::seqSettingUI);
	if (active_event)sequence_.change(&SubScene::seqEventUI);
	if (active_inventory)sequence_.change(&SubScene::seqInventoryUI);
	return true;
}
//勝手に一回呼び出し
bool SubScene::seqTutorialUI(float delta_time) {
	//コルーチン用
	while (1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "WASDキーで移動　Shiftで走る" };

			if (tnl::Input::IsKeyDown(eKeys::KB_W) ||
				tnl::Input::IsKeyDown(eKeys::KB_S) ||
				tnl::Input::IsKeyDown(eKeys::KB_A) ||
				tnl::Input::IsKeyDown(eKeys::KB_D))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "Ctrlでしゃがみ" };
			if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL))TNL_SEQ_CO_BREAK;
		});

		TNL_SEQ_CO_TIM_YIELD_RETURN(50, delta_time, [&]() {
			m_tutorial_message = { "物をひろう" };
			if (m_mediator->MGetLightParam())TNL_SEQ_CO_BREAK;
		});


		//ライトをGetしたかどうか
		
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "TABで持ち物をみる" };
			if (tnl::Input::IsKeyDown(eKeys::KB_TAB))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "Spaceでライトをつける" };
			if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
			m_tutorial_message = { "" };
				TNL_SEQ_CO_BREAK;
			
		});
		//チュートリアルの文字表示終了
		sequence_.change(&SubScene::seqIdle);
		
	}
	TNL_SEQ_CO_END;
	return true;
}

//Escapeを押されたら呼び出し、インベンとリーもTaｂ呼ばれたら呼び出し
bool SubScene::seqSettingUI(float delta_time) {
	//入力はマウスで移動距離を測定し、それにそった値に変化
	// バーの数値実際の音量の数値に設定
	//スタートへ戻るでブール値変化
	
	//シート２は
	//操作説明
	if (!active_option)sequence_.change(&SubScene::seqIdle);
	return true;
}

bool SubScene::seqEventUI(float delta_time) {
	
	//itemからの通知により、描画
	if (tnl::Input::IsMouseDown(eMouse::LEFT))sequence_.change(&SubScene::seqIdle);
	return true;
}

bool SubScene::seqInventoryUI(float delta_time) {
	if (!active_inventory)sequence_.change(&SubScene::seqIdle);
	return true;
}

//eventUIを呼び出すフラグ（Messageもここでいいかな）
//itemとかで呼び出し
//void SubScene::SetEvnetNotify(bool notice, int title) {
//	m_event_notify = notice;
//	m_message->ChangeStory(title);
//
//}