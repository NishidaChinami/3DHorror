#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../dxlib_ext/gui/dxlib_ext_gui_value_slider.h"
#include"BaseScene.h"

class OptionScene:public BaseScene
{
public:
	OptionScene(){}
	OptionScene(Shared<dxe::ScreenEffect> m_screen_efct);
	~OptionScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;

	void BarDraw();


	void SetBoolOption(bool option) { m_active_option = option; }
	bool GetBoolOption() { return m_active_option; }
	TNL_PROPERTY(float, Volume, m_volume);
	TNL_PROPERTY(float, Bright, m_bright);
	TNL_PROPERTY(float, Sensitive, m_sensitivity);

private:

	const static int MENU_NUM = 4;
	const static int SELECT_NUM = 3;
	const std::string MENU_LETTER[MENU_NUM] = { "操作説明","設定","ゲームに戻る","ゲームをやめる"};
	const std::string MENU_SELECT[SELECT_NUM] = { "音量","画面の明るさ","マウス感度"};

	bool m_active_option = false;
	//trueの時操作説明　falseのときは設定
	bool m_menu = false;
	//背景ハンドル
	int m_option_back_gpc = 0;
	//キーバインドのハンドル
	int m_keybind_hdl = 0;
	//各設定の変数（ｘ座標）
	float m_volume = 255;;
	float m_bright = 255;;
	float m_sensitivity = 0.1;

	const float OPTION_WIDTH = 720;
	const float OPTION_HEIGHT = 460;
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	const float RADIUS = 10;

	const tnl::Vector3 MENU_POS = { 250,360,0 };
	const tnl::Vector3 SELECT_POS = {490,220,0};
	const tnl::Vector2i PROGRESS_BAR_VOLUME = { 640,220};
	const tnl::Vector2i PROGRESS_BAR_BRIGHT = { 640,320};
	const tnl::Vector2i PROGRESS_BAR_SENSITIVITY = { 640,420};

	const tnl::Vector3 MENU_SIZE = { 100,50,0 };

	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_volume;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_bright;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_sensitive;
};

