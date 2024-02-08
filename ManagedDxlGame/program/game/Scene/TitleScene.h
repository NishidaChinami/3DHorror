#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class OptionScene;

//-------------------------------------------------------------------------------------------------//
//タイトルシーンクラス
//-------------------------------------------------------------------------------------------------//
class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	//プレイシーンの更新関数
	void Update(float delta_time)override;
	//プレイシーンの描画関数
	void Draw()override;	
	//動画再生コルーチン
	TNL_CO_SEQUENCE(TitleScene, &TitleScene::seqTitle);
	//子クラス追加
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}
private:
	//シーン遷移用のシーケンス
	tnl::Sequence<TitleScene> sequence_ = tnl::Sequence<TitleScene>(this, &TitleScene::seqTitle);
	bool seqTitle(float delta_time);//動画再生のコルーチンを回すシーケンス

	//タイトルの背景のグラフィックハンドル
	int m_title_gpc_hdl = 0;
	//動画読み込みの描画ハンドル
	int m_title_movie_hdl= 0;
	//動画再生用の画像ハンドル
	int m_title_screen_hdl = 0;	

	//------------他クラスの参照用ポインタ------------------------//
	//親クラスのリストを用意
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//子クラスであるオプションシーンクラスのリスト
	std::shared_ptr<OptionScene>m_option;
	//----------------------定数------------------------//
	//タイトルの文字のサイズ
	const float TITLE_FONT_SIZE = 40;
	//メニューの文字のサイズ
	const float MENU_FONT_SIZE = 30;
	//タイトルの文字の配列数
	const static int BUTTON_NUM = 4;
	//タイトルの文字数
	const static int TITLE_NUM = 5;

	//タイトル文字
	const std::string TITLE[TITLE_NUM] = { "恐","怖","の","風","説"};
	const tnl::Vector3 TITLE_SELECT_POS = { DXE_WINDOW_WIDTH / 2,500,0 };
	//文字の当たり判定のサイズ
	const tnl::Vector3 SELECT_SIZE = { 200,50, 0 };

	//選択項目の文字の色の配列
	int color_index[BUTTON_NUM] = { 0 };
	//タイトルの選択項目
	const std::string START_BUTTON[BUTTON_NUM] = { "ゲームを始める","チュートリアル","オプション","ゲームをやめる"};	
	//全角の１文字の大きさ
	const int FULLWIGHT = 2;
	//フェードの速度変数
	const float TRANS_TIME = 5.0f;

};

