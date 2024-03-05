#include "../dxlib_ext/dxlib_ext.h"
#include"../../Manager/Mediator.h"
#include"GameCamera.h"
#include"../../UI/OptionParam.h"


GameCamera::GameCamera() :Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {
	pos_ = { 0,HEAD_HEIGHT,0 };
}
GameCamera::~GameCamera()
{

}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void GameCamera::GameCameraUpdate(const std::shared_ptr<Mediator>& mediator) {
	//��t���[���O�̍��W��ۑ�
	m_prev_pos = pos_;
	//WASD�L�[�������ꂽ��A�e�x�N�g�������Ƀv���C���[�̃X�s�[�h���i��
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
	//�}�E�X���x��ݒ�Ŏ󂯎��
	m_sensitive = OptionParam::GetInstance()->getParamSensitive();
	//�J��������A�N�e�B�u�łȂ������ꍇ�}�E�X�ŃJ�����̉�]��������
	if (!m_camera_inactive) {
		tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
		m_camera_rot *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * m_sensitive));
		m_camera_rot *= tnl::Quaternion::RotationAxis(right(), tnl::ToRadian(mvel.y * m_sensitive));
	}
	
	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_camera_rot);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_camera_rot);
	dxe::Camera::Update();
	//�J������ʂ̒����̖@���x�N�g��
	m_ray = tnl::Vector3::CreateScreenRay(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, view_, proj_);
	//���Ⴊ�ݏ�Ԃ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LCONTROL)) {
		m_is_sneek == false ? m_is_sneek = true : m_is_sneek = false;
	}
	if(!m_is_sneek) {
		//���鎞�̐U���E�E�Eshift,W�L�[�Ƒ���t���O�������Ă��邩
		float pit = 0;
		tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) && tnl::Input::IsKeyDown(eKeys::KB_W) &&
			mediator->MGetPlayerDash() == true ? pit += 15 : pit = 0;
		pos_.y = HEAD_HEIGHT + sin(DX_PI_F / 180 * pit) * 1.0f;
		pos_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, fabs(sin(DX_PI_F / 180 * pit) * 3.0f) }, m_camera_rot);

	}
}
//------------------------------------------------------------------------------------------------------------
//�J�����Ɏʂ��Ă���̂�
bool GameCamera::OnCameraView(const tnl::Vector3 &target_pos) {
	//�t���X�^����6���ʂ������ɑ��݂��邩����
	//for (int i = 0; i < static_cast<int>(dxe::Camera::eFlustum::Near); i++) {
	//	if( - 1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i)), pos_))return false;
	//}
	////Near�ʂ�Far�ʂ̓J�������W���班�����W��ω�������
	//if (-1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(dxe::Camera::eFlustum::Far), pos_ + forward()*3000))return false;
	//if (-1 == tnl::GetSidesPointAndPlane(target_pos, getFlustumNormal(dxe::Camera::eFlustum::Near), pos_ - forward() * 1000))return false;

	return true;
}
//------------------------------------------------------------------------------------------------------------
//�J�����̐U��
void GameCamera::CameraVibration()
{
	float rum;
	static int time = 0;
	time += 3;
	if (time >= 180) time = 180;
	
	rum = sin(time * DX_PI_F / 180 * 50) * 20;
	pos_ += {rum, 0, 0};
}
