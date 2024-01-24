#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


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
	int m_backgroud_hdl = 0;
	std::string letter;


	int m_deathgpc_hdl = 0;
	int m_cleargpc_hdl = 0;
	static const int SELECT_NUM = 2;
	//文字の読み込みに失敗する？
	const std::string DEATH = { "あなたは死んだ" };
	const std::string SERECT[SELECT_NUM] = { "もう一度プレイ","タイトルへ戻る" };
	const std::string CLEAR = { "ゲームクリア" };

	const tnl::Vector3 CENTER_POS = { 300,360,0 };
	const tnl::Vector3 TITLE_POS = { 200, 600,0 };
	const tnl::Vector3 REPLAY_POS = { 500,600,0 };

	const tnl::Vector3 LETTER_SIZE = { 100,50,0 };
};

