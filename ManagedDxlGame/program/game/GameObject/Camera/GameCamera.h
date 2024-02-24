#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

//-------------------------------------------------------------------------------------------------//
//�J�����N���X
// �Q�[�����̈�l�̎��_�̃J����
//-------------------------------------------------------------------------------------------------//
class GameCamera : public dxe::Camera
{
public:
	GameCamera();
	~GameCamera();
	void GameCameraUpdate(const std::shared_ptr<Mediator>& mediator);
	//�J�����Ɏʂ��Ă���̂�
	bool OnCameraView(const tnl::Vector3 &target_pos);
	//�J�����̐U��
	void CameraVibration();

	//�J�����̏㉺���E�Ɖ��Ǝ�O�̃x�N�g���̎擾
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

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	const tnl::Vector3 &getRay() const{ return m_ray; }
	const tnl::Vector3 &GetScreenPos(tnl::Vector3 pos) const{return tnl::Vector3::ConvertToScreen({ pos.x, pos.y, pos.z }, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, view_, proj_); }
	const tnl::Vector3 &getPrevPos() const{ return m_prev_pos; }

	TNL_PROPERTY(tnl::Quaternion, CameraRot, m_camera_rot);
	TNL_PROPERTY(bool, CameraActive, m_camera_inactive);
	//-----------------�ÓI�萔--------------------------------//
	static constexpr float HEAD_HEIGHT = 400;
private:
	//�J�����̉�]
	tnl::Quaternion m_camera_rot;
	//�J�������牄�т�Ray
	tnl::Vector3 m_ray;
	//��t���[���O�̃J�����̍��W
	tnl::Vector3 m_prev_pos;
	//�}�E�X���x
	float m_sensitive = 0.1;
	//�J��������A�N�e�B�u���ǂ���
	bool m_camera_inactive = true;
	//���Ⴊ�݃t���O
	bool m_is_sneek = false;
};

