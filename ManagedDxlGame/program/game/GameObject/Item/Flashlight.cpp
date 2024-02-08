#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../../Manager/Mediator.h"
#include"Flashlight.h"
#include"../../Effect/Sound/Sound.h"

Flashlight::Flashlight()
{
	//�|�C���g���C�g�̐���������
	m_falshlight_hdl = CreateSpotLightHandle(VGet(0,0,0), VGet(0.0f, 0.0f, 1.0f), tnl::ToRadian(m_outangle), tnl::ToRadian(m_inangle), m_range, m_atten0, m_atten1, m_atten2);
	SetLightDifColorHandle(m_falshlight_hdl, GetColorF(0.2f, 0.2f, 0.37f,0));
	SetLightAmbColorHandle(m_falshlight_hdl, GetColorF(0.2f, 0.2f, 0.2f, 0));
	SetLightEnableHandle(m_falshlight_hdl, m_isvalid);
	
}

Flashlight::~Flashlight()
{
	DeleteLightHandle(m_falshlight_hdl);
}
//------------------------------------------------------------------------------------------------------------
//�����d����ON��OFF
void Flashlight::Update(tnl::Vector3 pos ,tnl::Quaternion rot) {
	//Space�Ń��C�g�n���h����L���ɂ����薳���ɂ����肷��
	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		Sound::GetInstance()->Sound2DPlay("FLASHLIGHT", DX_PLAYTYPE_BACK);
		m_isvalid == true ? m_isvalid = false : m_isvalid = true;
	}
	SetLightEnableHandle(m_falshlight_hdl, m_isvalid);
	//���C�g�̏Ƃ炷�������v���C���\�̐��ʂ̌����ɂ���
	SetLightPositionHandle(m_falshlight_hdl, cf::ConvertToV3(pos));
	SetLightDirectionHandle(m_falshlight_hdl, cf::ConvertToV3(tnl::Vector3::TransformCoord({ 0,0,1 }, rot)));
}

