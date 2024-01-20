#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/GameObject.h"


class GameCamera;

class Fluorescent : public GameObject
{
public:
	Fluorescent(tnl::Vector3 pos);
	~Fluorescent();
	void Update(float delta_time)override;
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	
private:

	tnl::Sequence<Fluorescent> sequence_ = tnl::Sequence<Fluorescent>(this, &Fluorescent::seqRed);
	bool seqRed(const float delta_time);
	bool seqNormal(const float delta_time);
	bool seqBlink(const float delta_time);

	
	//蛍光灯のハンドル
	int fluorescent_hdl;
	//蛍光灯の光る範囲
	float Range = 500;
	//光源の距離減衰の変数
	float Atten0 = 0;
	float Atten1 = 0.0006;
	float Atten2 = 0.0f;

	//フェードの速度変数
	float trans_time = 10.0f;
	//点滅のカウント
	float blink_count = 0;
	//点滅の間隔
	const float seconds = 3.0f;
};

