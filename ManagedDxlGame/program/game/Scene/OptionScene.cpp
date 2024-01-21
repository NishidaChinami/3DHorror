#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"OptionScene.h"
#include"../UI/OptionParam.h"

OptionScene::OptionScene()
{
	m_option_back_gpc = LoadGraph("graphics/PanelFrame.png");
}

OptionScene::~OptionScene()
{
	DeleteGraph(m_option_back_gpc);
}

void OptionScene::Update(float delta_time) {
	if (!m_active_option)return;
	auto param = OptionParam::GetInstance();
	
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 100, 0 };
		if (cf::IntersectMouse(pos, MENU_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				//case分のほうがよくない？
				if (i == 0)m_menu = true;
				if (i == 1)m_menu = false;
				if (i == 2) m_active_option = false;
				if (i == 3) {}//ゲームタイトルに戻る
			}
		}		
	}

	if (!m_menu) {
		tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
		if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
			//条件を付けるべき
			if (cf::IntersectMouse(tnl::Vector3(m_volume, PROGRESS_BAR_VOLUME.y, 0), tnl::Vector3(RADIUS)))
				if(param->sound_volume <= 255 && param->sound_volume >= 0)param->sound_volume += mvel.x; 
			if (cf::IntersectMouse(tnl::Vector3(m_bright, PROGRESS_BAR_VOLUME.y, 0), tnl::Vector3(RADIUS))) 
				if (param->screen_bright <= 255 && param->screen_bright >= 0)param->screen_bright += mvel.x;
			if (cf::IntersectMouse(tnl::Vector3(m_sensitivity, PROGRESS_BAR_VOLUME.y, 0), tnl::Vector3(RADIUS))) 
				if(param->mouse_sensitive > 0 && param->mouse_sensitive < 1)param->mouse_sensitive += mvel.x*0.1;
		}
		m_volume = PROGRESS_BAR_VOLUME.x - BAR_WIDTH / 2 + (param->sound_volume / BAR_WIDTH);
		m_bright = PROGRESS_BAR_VOLUME.x - BAR_WIDTH / 2 + (param->screen_bright / BAR_WIDTH);
		m_sensitivity = PROGRESS_BAR_VOLUME.x - BAR_WIDTH / 2 + (param->mouse_sensitive / BAR_WIDTH);

		/*for (int i = 0; i < SELECT_NUM; i++) {
			tnl::Vector3 pos = { PROGRESS_BAR_VOLUME.x,PROGRESS_BAR_VOLUME.y + i * 100,0 };
			float value = 0;
			if (i == 0)value = param->sound_volume;
			if(i == 1)value = param->screen_bright;
			if(i == 2)value = param->mouse_sensitive;
			if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
				if (cf::IntersectMouse(tnl::Vector3(m_param_index[i], pos.y, 0), tnl::Vector3(RADIUS)))
					if (param->sound_volume <= 255 && param->sound_volume >= 0)param->sound_volume += mvel.x;
			}
			
		}*/
	}
}

void OptionScene::Draw() {
	if (!m_active_option)return;
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.5, 1, m_option_back_gpc, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH+100, DXE_WINDOW_HEIGHT / 2, 0), OPTION_WIDTH, OPTION_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//文字の描画
	for (int i = 0; i < MENU_NUM; i++) {
		DrawStringEx(MENU_POS.x, MENU_POS.y + i * 100, -1, "%s", MENU_LETTER[i]);
	}
	if (m_menu) {
		//操作説明
		for (int i = 0; i < KEY_NUM; i++) {
			DrawStringEx(KEY_BIND_POS.x, KEY_BIND_POS.y + i * 100, -1, "%s", KEY_BIND[i]);
			DrawStringEx(OPERATION_POS.x, OPERATION_POS.y + i * 100, -1, "%s", OPERATION[i]);
		}
	}
	else {
		//設定
		/*DrawBoxEx(PROGRESS_BAR_VOLUME, BAR_WIDTH, BAR_HEIGHT, true, -1);
		DrawBoxEx(PROGRESS_BAR_BRIGHT, BAR_WIDTH, BAR_HEIGHT, true, -1);
		DrawBoxEx(PROGRESS_BAR_SENSITIVITY, BAR_WIDTH, BAR_HEIGHT, true, -1);
		DrawCircle(m_volume, PROGRESS_BAR_VOLUME.y,RADIUS,-1);
		DrawCircle(m_bright, PROGRESS_BAR_BRIGHT.y, RADIUS, -1);
		DrawCircle(m_sensitivity, PROGRESS_BAR_SENSITIVITY.y, RADIUS, -1);*/
		for (int i = 0; i < SELECT_NUM; i++) {
			tnl::Vector3 pos = { PROGRESS_BAR_VOLUME.x,PROGRESS_BAR_VOLUME.y + i * 100,0 };
			DrawBoxEx(pos, BAR_WIDTH, BAR_HEIGHT, true, -1);
			DrawCircle(m_param_index[i], PROGRESS_BAR_SENSITIVITY.y, RADIUS, -1);
		}
		
	}
}


