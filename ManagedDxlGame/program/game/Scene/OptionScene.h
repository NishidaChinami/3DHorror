#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class OptionScene:public BaseScene
{
public:
	OptionScene();
	~OptionScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;

	void SetBoolOption(bool option) { m_active_option = option; }
private:

	static const int MENU_NUM = 4;
	static const int SELECT_NUM = 3;
	static const int KEY_NUM = 12;
	const std::string MENU_LETTER[MENU_NUM] = { "操作説明","設定","ゲームに戻る","ゲームをやめる"};
	const std::string MENU_SELECT[SELECT_NUM] = { "音量","画面の明るさ","マウス感度"};
	const std::string KEY_BIND[KEY_NUM] = { "W","A","S""D","Shift","Ctrl","E","Space","Esc","Tab","マウス","右クリック"};
	const std::string OPERATION[KEY_NUM] = { "前進","左移動","右移動","後進","走る","しゃがむ","拾う/調べる","ライトをつける","設定画面を開く","持ち物を見る","視点移動","選択" };

	bool m_active_option = false;
	//trueの時操作説明　falseのときは設定
	bool m_menu = false;
	//背景ハンドル
	int m_option_back_gpc;
	//各設定の変数（ｘ座標）
	float m_volume;
	float m_bright;
	float m_sensitivity;

	float m_param_index[SELECT_NUM] = {m_volume,m_bright,m_sensitivity};

	const float OPTION_WIDTH = 800;
	const float OPTION_HEIGHT = 480;
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	const float RADIUS = 5;

	const tnl::Vector3 MENU_POS = { 150,360,0 };
	const tnl::Vector3 KEY_BIND_POS = { 390,120,0 };
	const tnl::Vector3 OPERATION_POS = { 490,220,0 };
	const tnl::Vector3 SELECT_POS = {390,120,0};
	const tnl::Vector3 PROGRESS_BAR_VOLUME = { 490,220,0 };
	const tnl::Vector3 PROGRESS_BAR_BRIGHT = { 490,320,0 };
	const tnl::Vector3 PROGRESS_BAR_SENSITIVITY = { 490,420,0 };

	const tnl::Vector3 MENU_SIZE = { 100,50,0 };
};

