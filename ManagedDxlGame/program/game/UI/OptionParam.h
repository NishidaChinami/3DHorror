#pragma once
#include "../dxlib_ext/dxlib_ext.h"

/// <summary>
/// 設定画面のパラメータークラス
/// </summary>
class OptionParam
{
public:
	OptionParam(){}
	~OptionParam(){}
	//シングルトン
	static OptionParam* GetInstance();
	//デストラクタ関数
	static void Destroy();

	//画面の明るさ
	float screen_bright = 255;
	//音の大きさ
	float sound_volume = 255;
	//マウスの感度(0.2~0.05)の範囲→0.15
	float mouse_sensitive = 0.1;
private:

};

