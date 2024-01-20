#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	//プレイシーンの更新関数
	void Update(float delta_time)override;
	//プレイシーンの描画関数
	void Draw()override;			
	TNL_CO_SEQUENCE(TitleScene, &TitleScene::seqTitle);
private:
	//シーン遷移用のテンプレート
	tnl::Sequence<TitleScene> sequence_ = tnl::Sequence<TitleScene>(this, &TitleScene::seqTitle);
	//結果画面またはスタート画面に戻る
	bool seqTitle(float delta_time);

	//タイトルの背景のグラフィックハンドル
	int title_gpc_hdl = 0;
	//動画読み込みの描画ハンドル
	int title_movie_hdl;
	//動画再生用の画像ハンドル
	int title_screen_hdl;	

	//タイトルの文字のサイズ
	const float TITLE_FONT_SIZE = 40;
	//メニューの文字のサイズ
	const float MENU_FONT_SIZE = 30;
	//タイトルの文字の配列数
	const static int BUTTON_NUM = 2;
	//タイトルの文字数
	const static int TITLE_NUM = 5;

	//タイトル文字
	const std::string TITLE[TITLE_NUM] = { "恐","怖","の","風","説"};

	//タイトルの選択項目
	const std::string START_BUTTON[BUTTON_NUM] = { "ゲームを始める","オプション" };
	//何文字表示したか数える変数
	int m_letter_count = 0;			
	//全角の１文字の大きさ
	const int FULLWIGHT = 2;
	//フェードの速度変数
	float trans_time = 5.0f;
	//透過の変数
	int alpha = 0;
};

