#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

//-------------------------------------------------------------------------------------------------//
//プレイヤーの前方を照らす懐中電灯
//-------------------------------------------------------------------------------------------------//
class Flashlight
{
public:
	Flashlight();
	~Flashlight();
	//第1引数　ライトを持つオブジェクトのポジション
	//第2引数　ライトを持つオブジェクトの向き
	void Update(tnl::Vector3 pos, tnl::Quaternion rot);

private:
	int m_falshlight_hdl;			//スポットタイプのライトハンドル

	bool m_isvalid = false;			//ライトが有効がどうか
	float m_range = 1000;			//ライトの有効距離
	//距離減衰パラメーター
	float m_atten0 = 0;				//ライトの頂点の距離に関係なく減衰する率を指定する
	float m_atten1 = 0.0006;		//ライトの距離に比例して減衰する率
	float m_atten2 = 0.0000f;		//ライトの距離の二乗に比例して減衰する率
	float m_outangle = 45.0f;		//スポットライトコーンの外側の角度
	float m_inangle = 30.0f;		//スポットライトコーンの内側の角度

};

