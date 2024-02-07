#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../dxlib_ext/gui/dxlib_ext_gui_value_slider.h"
#include"BaseScene.h"

//-------------------------------------------------------------------------------------------------//
//BaseScene継承のオプション画面のクラス
// TitleやPlay,TutorialSceneの子クラスとして機能する
// Componentパターンを模して作成した。次回はよりパターンの構造に近くする
//-------------------------------------------------------------------------------------------------//
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
	//スライダーの描画関数
	void BarDraw();
	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(bool, ShowOption, m_active_option);
	TNL_PROPERTY(float, Volume, m_volume);
	TNL_PROPERTY(float, Bright, m_bright);
	TNL_PROPERTY(float, Sensitive, m_sensitivity);
	TNL_PROPERTY(bool, TitleIsValid, m_title_isvalid);

	//オプション画面の文字
	const static int MENU_NUM = 4;
	const static int SELECT_NUM = 3;
private:
	//オプション画面が開かれているかどうか
	bool m_active_option = false;
	//タイトル画面かどうか
	bool m_title_isvalid = false;
	//遊び方か設定画面かを分けるフラグ
	//trueの時操作説明　falseのときは設定
	bool m_menu = false;
	//背景ハンドル
	int m_option_back_gpc = 0;
	//キーバインドのハンドル
	int m_keybind_hdl = 0;

	//各設定の変数（ｘ座標）
	float m_volume = 255;
	float m_bright = 255;
	float m_sensitivity = 0.1;
	
	//文字の色の配列
	int color_index[MENU_NUM] = { 0 };

	//------------他クラスの参照用ポインタ------------------------//
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_volume;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_bright;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_sensitive;
	//----------------------定数------------------------//
	//オプション画面の文字
	const std::string MENU_LETTER[MENU_NUM] = { "操作説明","設定","ゲームに戻る","ゲームをやめる" };
	const std::string MENU_SELECT[SELECT_NUM] = { "音量","画面の明るさ","マウス感度" };
	//オプション画面のボックスのサイズ
	const float OPTION_WIDTH = 720;
	const float OPTION_HEIGHT = 460;
	//スライダーのボックスのサイズ
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	//つまみの半径
	const float RADIUS = 10;

	//設定画面の項目の先頭座標
	const tnl::Vector3 MENU_POS = { 250,360,0 };
	//音量や明るさ等の選択項目の先頭座標
	const tnl::Vector3 SELECT_POS = { 490,220,0 };
	//各項目のスライダーの座標
	const tnl::Vector2i PROGRESS_BAR_VOLUME = { 640,220 };
	const tnl::Vector2i PROGRESS_BAR_BRIGHT = { 640,320 };
	const tnl::Vector2i PROGRESS_BAR_SENSITIVITY = { 640,420 };

	//文字の当たり判定のサイズ
	const tnl::Vector3 MENU_SIZE = { 200,50,0 };
	//フォントサイズ
	const int MENU_FONT = 18;
};

