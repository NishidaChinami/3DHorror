#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../../Manager/Mediator.h"
#include"Fluorescent.h"
#include"../../GameObject/Camera/GameCamera.h"

Fluorescent::Fluorescent(const tnl::Vector3 &pos, const std::shared_ptr<Mediator>& mediator)
{
	//見えないメッシュ生成
	mesh = dxe::Mesh::CreateCubeMV(LIGHT_SIZE);
	//座標を受け取る
	mesh->pos_ = { pos.x,500,pos.z };
	m_mediator = mediator;
	//ライトハンドルの生成と初期設定
	m_fluorescent_hdl = CreatePointLightHandle(cf::ConvertToV3(mesh->pos_), m_range, m_atten0, m_atten1, m_atten2);
	SetLightDifColorHandle(m_fluorescent_hdl, GetColorF(0.2f, 0.2f, 0.2f, 0));
	SetLightSpcColorHandle(m_fluorescent_hdl, GetColorF(0, 0, 0, 0));
	SetLightEnableHandle(m_fluorescent_hdl, false);
}



Fluorescent::~Fluorescent()
{
	DeleteLightHandle(m_fluorescent_hdl);
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void Fluorescent::Update(float delta_time) {
	//SetLightPositionHandle(m_fluorescent_hdl, cf::ConvertToV3( tnl::Vector3(m_mediator->MGetEnemyPos().x,500, m_mediator->MGetEnemyPos().z)));
	//敵との距離によって有効にするライトハンドルを決める
	if (tnl::IsIntersectSphere(mesh->pos_ - tnl::Vector3(0,250,0), LIGHT_SIZE, m_mediator->MGetEnemyPos(), RANGE)) {
		is_valid = true;
		//減衰率を下げて明るく
		m_atten1 = 0.0009;
		Blink(delta_time);
	}
	else {
		//減衰率を上げて暗くなったら無効にする
		m_atten1 *= 1.01f;
		if (m_atten1 > 0.9) {
			is_valid = false;
			m_atten1 = 0.9;
		}
	}
	SetLightRangeAttenHandle(m_fluorescent_hdl, m_range, m_atten0, m_atten1, m_atten2);
	SetLightEnableHandle(m_fluorescent_hdl, is_valid);
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void Fluorescent::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//カメラに写ってたら
	//if (gamecamera->OnCameraView(mesh->pos_)) {}
}

//------------------------------------------------------------------------------------------------------------
//点滅処理
void Fluorescent::Blink(const float delta_time) {

	float bright = 0;
	m_blink_count += delta_time;
	//0～１の間を行ったり来たりする
	bright = fabs(sin(DX_PI_F / 180 * m_blink_count));
	//半周期立つと点滅速度を変更
	if (m_blink_count >= tnl::ToDegree(DX_PI_F)) {
		bright = fabs(sin(DX_PI_F / 180 * m_blink_count * m_trans_time));
		//一回点滅すると速度が戻る
		if (m_blink_count >= (tnl::ToDegree(DX_PI_F)+ SECONDS))m_blink_count = 0;
	}
	//Difカラーで赤い点滅に指定
	SetLightDifColorHandle(m_fluorescent_hdl,GetColorF(bright, 0, 0, 0));

}