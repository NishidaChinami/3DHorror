#include "../dxlib_ext/dxlib_ext.h"
#include"GameCamera.h"
#include"../../Manager/Mediator.h"


GameCamera::GameCamera() :Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {
	pos_ = { 0,200,0 };
}
GameCamera::~GameCamera()
{
}

void GameCamera::GameCameraUpdate(const std::shared_ptr<Mediator>& mediator) {

	m_prev_pos = pos_;

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				left(),
				right(),
				forward().xz(),
				back().xz()
			};
			pos_ += v[index] * mediator->MGetPlayerSpeed();

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
	m_camera_rot *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * m_sensitive));
	m_camera_rot *= tnl::Quaternion::RotationAxis(right(), tnl::ToRadian(mvel.y * m_sensitive));
	
	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_camera_rot);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_camera_rot);
	dxe::Camera::Update();

	m_ray = tnl::Vector3::CreateScreenRay(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, view_, proj_);
}
//ÉJÉÅÉâÇ…é Ç¡ÇƒÇ¢ÇÈÇÃÇ©
bool GameCamera::OnCameraView(tnl::Vector3 target_pos) {
	for (int i = 0; i < static_cast<int>(dxe::Camera::eFlustum::Near); i++) {
		if (-1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i)), pos_))return false;
	}
	if (-1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(dxe::Camera::eFlustum::Far), pos_ + forward()*2000))return false;
	if (-1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(dxe::Camera::eFlustum::Near), pos_ - forward() * 1000))return false;

	return true;
}

void GameCamera::CameraVibration()
{
	float rum;
	static int time = 0;
	time += 3;
	if (time > 360) { time = 0; }
	rum = sin(time * DX_PI_F / 180 * 50) * 20;
	pos_ += {rum, 0, rum};
}
