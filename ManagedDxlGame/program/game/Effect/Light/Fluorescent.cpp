#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Fluorescent.h"
#include"../../GameObject/Camera/GameCamera.h"
//カメラの描画内に入ったときライトハンドルを持たせる風にする
//フラスタム

Fluorescent::Fluorescent(tnl::Vector3 pos)
{
	mesh = dxe::Mesh::CreateCubeMV(10);
	mesh->pos_ = pos;
	fluorescent_hdl = CreatePointLightHandle(cf::ConvertToV3(mesh->pos_), Range, Atten0, Atten1, Atten2);
	SetLightDifColorHandle(fluorescent_hdl, GetColorF(0.2f, 0.2f, 0.2f, 0));
	SetLightSpcColorHandle(fluorescent_hdl, GetColorF(0, 0, 0, 0));

}

Fluorescent::~Fluorescent()
{
	DeleteLightHandle(fluorescent_hdl);
}

void Fluorescent::Update(float delta_time) {
	SetLightEnableHandle(fluorescent_hdl, is_alive);
	sequence_.Update(delta_time);
}
void Fluorescent::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//カメラに写ってたら
	if (gamecamera->OnCameraView(mesh->pos_)) {
		is_alive = true;
	}
	else is_alive = false;
}




bool Fluorescent::seqNormal(const float delta_time) {
	SetLightDifColorHandle(fluorescent_hdl, GetColorF(0.2f, 0.2f, 0.2f, 0));
	return true;
}

bool Fluorescent::seqRed(const float delta_time) {
	//だんだん位置に向かうようにする赤の色だけ
	float alpha = (sequence_.getProgressTime() / trans_time * 1.0f);
	if (alpha >= 1) {
		SetLightDifColorHandle(fluorescent_hdl, GetColorF(1.0f, 0.0f, 0.0f, 0));
	}
	SetLightDifColorHandle(fluorescent_hdl, GetColorF(alpha, 0.0f, 0.0f, 0));
	return true;
}

bool Fluorescent::seqBlink(const float delta_time) {
	 //点滅処理
	/*static float time = 0;
	static float bright = 0;
	time++;
	bright = fabs(sin(DX_PI_F / 180 * time));
	if (time >= 360) {
		bright = fabs(sin(DX_PI_F / 180 * time * 4));
		if (time >= 450)time = 0;
	}
	SetLightDifColor(GetColorF(bright / 4, bright / 4, bright / 4, 1));
	SetLightSpcColor(GetColorF(bright / 4, bright / 4, bright / 4, 1));*/

	return true;
}