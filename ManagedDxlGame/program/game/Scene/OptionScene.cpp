#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../Manager/Manager.h"
#include"OptionScene.h"
#include"../UI/OptionParam.h"
#include"TitleScene.h"
#include"../Effect/Sound/Sound.h"

OptionScene::OptionScene(Shared<dxe::ScreenEffect> m_screen_efct)
{
	//画像の読み込み
	m_option_back_gpc = LoadGraph("graphics/PanelFrame.png");
	m_keybind_hdl = LoadGraph("graphics/keybind.png");
	//初期化
	auto param = OptionParam::GetInstance();
	m_volume = param->getParamVolume();
	m_bright = param->getParamBright();
	m_sensitivity = param->getParamSensitive();

	screen_efct = m_screen_efct;
}

OptionScene::~OptionScene()
{
	DeleteGraph(m_option_back_gpc);
	DeleteGraph(m_keybind_hdl);
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void OptionScene::Update(float delta_time) {
	if (!m_active_option)return;
	auto param = OptionParam::GetInstance();
	auto sound = Sound::GetInstance();
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 50, 0 };
		color_index[i] = cf::IntersectMouse(pos, MENU_SIZE) ? -1 : 0;
		//0x88888888
		if (cf::IntersectMouse(pos, MENU_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				sound->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
				//メニューの選択時の処理
				switch (i)
				{
					//設定画面
					case 0:m_menu = true; break;
					//遊び方
					case 1:m_menu = false; break;
					//ゲームを再開
					case 2: {
						m_active_option = false; 
						break;
					}
					//タイトルに戻る
					case 3:
						if(m_title_isvalid)m_active_option = false;
						else {
							auto manager = GameManager::GetInstance();
							manager->ChangeScene(std::make_shared<TitleScene>());
						}
						break;
				}
			}
		}		
	}

	if (!m_menu) {
	//オプションパラメーターに代入
		param->setParamVolume(m_volume);
		param->setParamBright(m_bright);
		param->setParamSensitive(m_sensitivity);
	}
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void OptionScene::Draw() {
	if (!m_active_option) { return; }
	//オプション画面の背景
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DIANETER, 0, m_option_back_gpc, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(BACK_POS, OPTION_WIDTH, OPTION_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//メニュー項目の文字の描画
	SetFontSize(MENU_FONT);
	ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 50,0 };
		cf::DrawCenterString(MENU_LETTER[i].c_str(), pos, color_index[i]);
	}
	if (m_menu) {
		//操作説明
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2 + 100, DXE_WINDOW_HEIGHT / 2, 1, 0, m_keybind_hdl, true);
	}
	else {
		//スライダーの描画
		BarDraw();
		//設定画面の選択項目の文字の描画
		for (int i = 0; i < SELECT_NUM; i++) {
			DrawStringEx(SELECT_POS.x, SELECT_POS.y + i * 100, -1, "%s", MENU_SELECT[i].c_str());
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//スライダーの描画の処理
void OptionScene::BarDraw()
{
	
	if (!gui_volume) {
		gui_volume = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getVolume,
				&OptionScene::setVolume,
				PROGRESS_BAR_VOLUME,
				MIN_VOLUME,
				MAX_VOLUME,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	if (!gui_bright) {
		gui_bright = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getBright,
				&OptionScene::setBright,
				PROGRESS_BAR_BRIGHT,
				MIN_VOLUME,
				MAX_VOLUME,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	if (!gui_sensitive) {
		gui_sensitive = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getSensitive,
				&OptionScene::setSensitive,
				PROGRESS_BAR_SENSITIVITY,
				MIN_SENSITIVITY,
				MAX_SENSITIVITY,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	gui_bright->Update();
	gui_volume->Update();
	gui_sensitive->Update();
	gui_bright->draw();
	gui_volume->draw();
	gui_sensitive->draw();
}


