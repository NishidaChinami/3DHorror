#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../../Manager/Mediator.h"
#include"Fluorescent.h"
#include"../../GameObject/Camera/GameCamera.h"

Fluorescent::Fluorescent(const tnl::Vector3 &pos, const std::shared_ptr<Mediator>& mediator)
{
	//�����Ȃ����b�V������
	mesh = dxe::Mesh::CreateCubeMV(LIGHT_SIZE);
	//���W���󂯎��
	mesh->pos_ = { pos.x,500,pos.z };
	m_mediator = mediator;
	//���C�g�n���h���̐����Ə����ݒ�
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
//�X�V����
void Fluorescent::Update(float delta_time) {
	//SetLightPositionHandle(m_fluorescent_hdl, cf::ConvertToV3( tnl::Vector3(m_mediator->MGetEnemyPos().x,500, m_mediator->MGetEnemyPos().z)));
	//�G�Ƃ̋����ɂ���ėL���ɂ��郉�C�g�n���h�������߂�
	if (tnl::IsIntersectSphere(mesh->pos_ - tnl::Vector3(0,250,0), LIGHT_SIZE, m_mediator->MGetEnemyPos(), RANGE)) {
		is_valid = true;
		//�������������Ė��邭
		m_atten1 = 0.0009;
		Blink(delta_time);
	}
	else {
		//���������グ�ĈÂ��Ȃ����疳���ɂ���
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
//�`�揈��
void Fluorescent::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//�J�����Ɏʂ��Ă���
	//if (gamecamera->OnCameraView(mesh->pos_)) {}
}

//------------------------------------------------------------------------------------------------------------
//�_�ŏ���
void Fluorescent::Blink(const float delta_time) {

	float bright = 0;
	m_blink_count += delta_time;
	//0�`�P�̊Ԃ��s�����藈���肷��
	bright = fabs(sin(DX_PI_F / 180 * m_blink_count));
	//���������Ɠ_�ő��x��ύX
	if (m_blink_count >= tnl::ToDegree(DX_PI_F)) {
		bright = fabs(sin(DX_PI_F / 180 * m_blink_count * m_trans_time));
		//���_�ł���Ƒ��x���߂�
		if (m_blink_count >= (tnl::ToDegree(DX_PI_F)+ SECONDS))m_blink_count = 0;
	}
	//Dif�J���[�ŐԂ��_�łɎw��
	SetLightDifColorHandle(m_fluorescent_hdl,GetColorF(bright, 0, 0, 0));

}