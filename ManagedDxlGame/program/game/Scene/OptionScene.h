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
private:
	//選択画面用のテンプレート
	tnl::Sequence<OptionScene> sequence_ = tnl::Sequence<OptionScene>(this, &OptionScene::seqOption);
	bool seqOption(float delta_time);
	bool seqIdle(float delta_time);
	const std::string MENU_LETTER[3] = { "操作説明","設定","ゲームに戻る"};
	const std::string MENU_SELECT[3] = { "音量","画面の明るさ","マウス感度"};

	bool active_option = false;
	//trueの時操作説明　falseのときは設定
	bool menu = false;
	//背景ハンドル
	int option_back_gpc;
	int select_gpc;
};

