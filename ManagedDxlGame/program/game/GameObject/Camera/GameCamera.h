#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

class GameCamera : public dxe::Camera
{
public:
	GameCamera();
	~GameCamera();
	void GameCameraUpdate(const std::shared_ptr<Mediator>& mediator);
	//ƒJƒƒ‰‚ÉÊ‚Á‚Ä‚¢‚é‚Ì‚©
	bool OnCameraView(tnl::Vector3 target_pos);
	//ƒJƒƒ‰‚ÌU“®
	void CameraVibration();

	inline tnl::Vector3 Up() {
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_camera_rot);
		return up_;
	}
	inline tnl::Vector3 Down() { return -Up(); }

	inline tnl::Vector3 forward() override {
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_camera_rot);
		return tnl::Vector3::Normalize(target_ - pos_);
	}
	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), Up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(Up(), forward()); }


	tnl::Quaternion GetCameraRot() { return m_camera_rot; }
	tnl::Vector3 GetRay() { return m_ray; }
	tnl::Vector3 GetScreenPos(tnl::Vector3 pos) {return tnl::Vector3::ConvertToScreen({ pos.x, pos.y, pos.z }, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, view_, proj_); }
	tnl::Vector3 GetPrevPos() { return m_prev_pos; }
private:
	//ƒJƒƒ‰‚Ì‰ñ“]
	tnl::Quaternion m_camera_rot;
	tnl::Quaternion m_player_rot;
	tnl::Vector3 m_distance = { 0, 200, -100.0f };
	tnl::Vector3 m_size;
	tnl::Vector3 m_ray;
	tnl::Vector3 m_prev_pos;

	float m_sensitive = 0.1;
};

