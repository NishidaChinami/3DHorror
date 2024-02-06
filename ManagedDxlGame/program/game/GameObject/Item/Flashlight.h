#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

//-------------------------------------------------------------------------------------------------//
//�v���C���[�̑O�����Ƃ炷�����d��
//-------------------------------------------------------------------------------------------------//
class Flashlight
{
public:
	Flashlight();
	~Flashlight();
	//��1�����@���C�g�����I�u�W�F�N�g�̃|�W�V����
	//��2�����@���C�g�����I�u�W�F�N�g�̌���
	void Update(tnl::Vector3 pos, tnl::Quaternion rot);

private:
	int m_falshlight_hdl;			//�X�|�b�g�^�C�v�̃��C�g�n���h��

	bool m_isvalid = false;			//���C�g���L�����ǂ���
	float m_range = 1000;			//���C�g�̗L������
	//���������p�����[�^�[
	float m_atten0 = 0;				//���C�g�̒��_�̋����Ɋ֌W�Ȃ��������闦���w�肷��
	float m_atten1 = 0.0006;		//���C�g�̋����ɔ�Ⴕ�Č������闦
	float m_atten2 = 0.0000f;		//���C�g�̋����̓��ɔ�Ⴕ�Č������闦
	float m_outangle = 45.0f;		//�X�|�b�g���C�g�R�[���̊O���̊p�x
	float m_inangle = 30.0f;		//�X�|�b�g���C�g�R�[���̓����̊p�x

};

