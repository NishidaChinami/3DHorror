#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

//-------------------------------------------------------------------------------------------------//
//リザルトクラス
// シーンのエンディング等の描画
//-------------------------------------------------------------------------------------------------//
class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;
private:
	//エンディングの背景と文字の保存する変数
	int m_background_hdl = 0;
	std::string letter;
	
	//ゲームクリアとゲームオーバーの背景ハンドル
	int m_deathgpc_hdl = 0;
	int m_cleargpc_hdl = 0;

	//----------------------定数------------------------//
	static const int SELECT_NUM = 2;
	//リザルトで使う文字
	const std::string DEATH = { "あなたは死んだ" };
	const std::string SERECT[SELECT_NUM] = { "タイトルへ戻る","もう一度プレイ" };
	const std::string CLEAR = { "ゲームクリア" };
	//各文字の座標
	const tnl::Vector3 CENTER_POS = { 640,360,0 };
	const tnl::Vector3 TITLE_POS = { 540, 600,0 };
	const tnl::Vector3 REPLAY_POS = { 740,600,0 };
	//文字の当たり判定のサイズ
	const tnl::Vector3 LETTER_SIZE = { 100,50,0 };
	//文字のフォントサイズ
	const float RESULT_FONT_SIZE = 50;
	const float SELECT_FONT_SIZE = 20;
};

