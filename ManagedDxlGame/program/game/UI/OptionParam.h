#pragma once
#include "../dxlib_ext/dxlib_ext.h"

//-------------------------------------------------------------------------------------------------//
//�ݒ��ʂ̃p�����[�^�[�N���X
// �V���O���g���p�^�[���Ŏ���
//-------------------------------------------------------------------------------------------------//
class OptionParam
{
public:
	~OptionParam(){}
	//�V���O���g��
	static OptionParam* GetInstance();
	//�f�X�g���N�^�֐�
	static void Destroy();

	////��ʂ̖��邳
	//float screen_bright = 255;
	////���̑傫��
	//float sound_volume = 255;
	////�}�E�X�̊��x(0.2~0.05)�͈̔�
	//float mouse_sensitive = 0.1;

	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(float, ParamBright, m_screen_bright);
	TNL_PROPERTY(float, ParamVolume, m_sound_volume);
	TNL_PROPERTY(float, ParamSensitive, m_mouse_sensitive);
private:
	OptionParam(){}
	//��ʂ̖��邳
	float m_screen_bright = 255;
	//���̑傫��
	float m_sound_volume = 255;
	//�}�E�X�̊��x(0.2~0.05)�͈̔�
	float m_mouse_sensitive = 0.1;
};

