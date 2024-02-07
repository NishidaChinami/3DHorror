#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../Manager/Manager.h"
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
//-------------------Scene file------------------------//
#include"SubScene.h"
//-------------------GameObject file------------------------//
#include"PlayScene.h"
#include"../GameObject/Character/Player/Player.h"
//-------------------UI file------------------------//
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"

SubScene::SubScene(std::shared_ptr<Factory> factory, std::shared_ptr<Mediator> mediator) :m_factory(factory), m_mediator(mediator)
{
	//チュートリアルで使うデータのインスタンス生成
	m_tutorial_date.emplace_back("WASDキーで移動", eKeys::KB_W, false);
	m_tutorial_date.emplace_back("Shiftで走る", eKeys::KB_LSHIFT, false);
	m_tutorial_date.emplace_back("Ctrlでしゃがみ", eKeys::KB_LCONTROL, true);
	m_tutorial_date.emplace_back("TABで持ち物をみる", eKeys::KB_TAB, true);
	m_tutorial_date.emplace_back("SPACEでライトをつける", eKeys::KB_SPACE, true);

}

SubScene::~SubScene()
{

}
//------------------------------------------------------------------------------------------------------------
//更新処理
void SubScene::Update(float delta_time) {
	sequence_.Update(delta_time);
}
//------------------------------------------------------------------------------------------------------------
//描画関数
void SubScene::Draw() {
	auto manager = GameManager::GetInstance();
	ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
	//イベントUIの描画
	if (m_active_event) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH/2, DXE_WINDOW_HEIGHT/2, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(EVENT_FONT);
		m_factory->GetClassMessage()->MessageDraw();
	}
	//インベントリーUIの描画
	else if (m_active_inventory) {
		SetFontSize(INVENTORY_FONT);
		m_factory->GetClassInventory()->Draw();
	}
	//イベントUIが開いてないときのUI描画
	else {
		//画面の中心
		//SetFontSize(10);
		DrawStringEx(640, 360, -1, "・");
		//走るときのスタミナゲージ
		if (m_mediator->MGetPlayerStamina() < Player::MAXSTAMINA) {
			DrawBoxEx(DASHGAUGE_POS, m_mediator->MGetPlayerStamina() / 2, GAUGE_HEIGHT, true, -1);
		}
		
	}
	//チュートリアル中の文字の描画
	if (m_active_tutorial) {
		SetFontSize(TUTORIAL_FONT);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		cf::DrawCenterString(m_tutorial_message.c_str(),TUTORIAL_MESSEAGE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	
}
//------------------------------------------------------------------------------------------------------------
//UIの待機状態
bool SubScene::seqIdle(float delta_time) {
	if (m_active_event)sequence_.change(&SubScene::seqEventUI); 
	if (m_active_inventory)sequence_.change(&SubScene::seqInventoryUI);
	if (GameManager::GetInstance()->is_tutorial && m_active_tutorial)sequence_.change(&SubScene::seqTutorialUI);
	return true;

}
//------------------------------------------------------------------------------------------------------------
//操作チュートリアルのアップデート
bool SubScene::seqTutorialUI(float delta_time) {
	auto sound = Sound::GetInstance();
	if (m_active_event) {
		sequence_.change(&SubScene::seqEventUI);
		m_active_tutorial = false;
		return true;
	}
	m_time_count++;
	//操作説明の情報をコルーチンで一つづつ描画
	auto  date_index = m_tutorial_date.begin();
	while (date_index != m_tutorial_date.end()) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			//20秒間指示を表示
			m_tutorial_message = date_index->s_mess.c_str();
			//文字のフェードイン
			if (m_time_count >= 255)m_time_count = 255;
			m_alpha = m_time_count;
			//指示のキーが押されたら次の指示へ
			if (tnl::Input::IsKeyDownTrigger(date_index->s_key)) {
				m_time_count = 0;
				TNL_SEQ_CO_BREAK;
			}
		});
		TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {
			//文字のフェードアウト
			m_alpha = 255 - m_time_count * 3;
			if (m_time_count >= 255)m_time_count = 255;
		});
		TNL_SEQ_CO_TIM_YIELD_RETURN(30, delta_time, [&]() {
			if (m_mediator->MGetLightParam() == date_index->s_light_flug) TNL_SEQ_CO_BREAK;
		});
		date_index++;
		if (date_index == m_tutorial_date.end()) {
			m_tutorial_message = { "" };
			m_active_tutorial = false;
			//チュートリアルの文字表示終了
			sequence_.change(&SubScene::seqIdle);
			return true;
		}
	}
	TNL_SEQ_CO_END;
	return true;
}
//------------------------------------------------------------------------------------------------------------
//イベントUIの更新
bool SubScene::seqEventUI(float delta_time) {
	auto manager = GameManager::GetInstance();
	//右クリックすると待機状態に戻る
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		m_active_event = false;
		sequence_.change(&SubScene::seqIdle);
		if (m_mediator->MGetTitleType() == 0) {
			manager->ChangeScene(std::make_shared<PlayScene>());
			manager->is_tutorial = false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------------------------------------
//インベントリーの更新
bool SubScene::seqInventoryUI(float delta_time) {
	if (!m_active_inventory)sequence_.change(&SubScene::seqIdle);
	return true;
}


