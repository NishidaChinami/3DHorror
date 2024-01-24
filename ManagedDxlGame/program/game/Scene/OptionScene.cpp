#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../Manager/Manager.h"
#include"OptionScene.h"
#include"../UI/OptionParam.h"
#include"TitleScene.h"

OptionScene::OptionScene(Shared<dxe::ScreenEffect> m_screen_efct)
{
	m_option_back_gpc = LoadGraph("graphics/PanelFrame.png");
	m_keybind_hdl = LoadGraph("graphics/keybind.png");
	screen_efct = m_screen_efct;
}

OptionScene::~OptionScene()
{
	DeleteGraph(m_option_back_gpc);
}

void OptionScene::Update(float delta_time) {
	if (!m_active_option)return;
	auto param = OptionParam::GetInstance();
	
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 50, 0 };
		if (cf::IntersectMouse(pos, MENU_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				//case•ª‚Ì‚Ù‚¤‚ª‚æ‚­‚È‚¢H
				if (i == 0)m_menu = true;
				if (i == 1)m_menu = false;
				if (i == 2) m_active_option = false;
				if (i == 3) {
					auto manager = GameManager::GetInstance();
					manager->ChangeScene(std::make_shared<TitleScene>());
				}
			}
		}		
	}

	if (!m_menu) {
	
		param->sound_volume = m_volume;
		param->screen_bright = m_bright;
		param->mouse_sensitive = m_sensitivity;

	}
}

void OptionScene::Draw() {
	if (!m_active_option)return;
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.5, 0, m_option_back_gpc, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH	/2+100, DXE_WINDOW_HEIGHT / 2, 0), OPTION_WIDTH, OPTION_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//•¶Žš‚Ì•`‰æ
	for (int i = 0; i < MENU_NUM; i++) {
		DrawStringEx(MENU_POS.x, MENU_POS.y + i * 50, -1, "%s", MENU_LETTER[i].c_str());
	}
	if (m_menu) {
		//‘€ìà–¾
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2 + 100, DXE_WINDOW_HEIGHT / 2, 1, 0, m_keybind_hdl, true);
	}
	else {
		//Ý’è
		BarDraw();
		//•¶Žš
		for (int i = 0; i < SELECT_NUM; i++) {
			DrawStringEx(SELECT_POS.x, SELECT_POS.y + i * 100, -1, "%s", MENU_SELECT[i].c_str());
		}
	}
}

void OptionScene::BarDraw()
{
	
	if (!gui_volume) {
		gui_volume = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this
				, &OptionScene::getVolume
				, &OptionScene::setVolume
				, PROGRESS_BAR_VOLUME
				, 0.0f
				, 255.0f
				, ""
				,300));
	}
	if (!gui_bright) {
		gui_bright = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this
				, &OptionScene::getBright
				, &OptionScene::setBright
				, PROGRESS_BAR_BRIGHT
				, 0.0f
				, 255.0f
				, ""
				, 300));
	}
	if (!gui_sensitive) {
		gui_sensitive = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this
				, &OptionScene::getSensitive
				, &OptionScene::setSensitive
				, PROGRESS_BAR_SENSITIVITY
				, 0.05f
				, 0.2f
				, ""
				, 300));
	}
	gui_bright->Update();
	gui_volume->Update();
	gui_sensitive->Update();
	gui_bright->draw();
	gui_volume->draw();
	gui_sensitive->draw();
}


