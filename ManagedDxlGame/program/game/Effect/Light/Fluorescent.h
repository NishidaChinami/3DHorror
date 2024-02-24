#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/GameObject.h"


class GameCamera;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//オブジェクトクラス
//ほかのオブジェクトの親クラス
// メッシュのポインタやサイズ、座標などをメンバ変数にもつ
//-------------------------------------------------------------------------------------------------//
class Fluorescent : public GameObject
{
public:
	//生成座標と他オブジェクトの参照をもつメディエータークラスを引数に持つ
	Fluorescent(const tnl::Vector3 &pos, const std::shared_ptr<Mediator>&mediator);
	~Fluorescent();
	//更新処理
	void Update(float delta_time)override;
	//描画処理
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//光の点滅処理
	void Blink(float delta_time);

	
private:
	//蛍光灯のハンドル
	int m_fluorescent_hdl;

	float m_range = 4000;			//ライトの有効距離
	//距離減衰パラメーター
	float m_atten0 = 0;				//ライトの頂点の距離に関係なく減衰する率を指定する
	float m_atten1 = 0.0009;		//ライトの距離に比例して減衰する率
	float m_atten2 = 0.0000f;		//ライトの距離の二乗に比例して減衰する率

	//点滅の速度変数
	float m_trans_time =0;
	//点滅のカウント
	float m_blink_count = 0;

	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Mediator>m_mediator = nullptr;

	//----------------------定数------------------------//
	//点滅の間隔
	const float SECONDS = 45;
	//電球のメッシュのサイズ
	const int LIGHT_SIZE = 10;
	//敵との近さを判定する範囲
	const int RANGE = 800;
	//蛍光灯の光の通常速度
	const float TRANS_TIME = 2.0f;
	//速度の変化の範囲
	const int TRANS_RANGE = 6;
};

