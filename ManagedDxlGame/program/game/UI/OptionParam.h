#pragma once
#include "../dxlib_ext/dxlib_ext.h"

/// <summary>
/// �ݒ��ʂ̃p�����[�^�[�N���X
/// </summary>
class OptionParam
{
public:
	OptionParam(){}
	~OptionParam(){}
	//�V���O���g��
	static OptionParam* GetInstance();
	//�f�X�g���N�^�֐�
	static void Destroy();

	//��ʂ̖��邳
	float screen_bright = 255;
	//���̑傫��
	float sound_volume = 255;
	//�}�E�X�̊��x(0.2~0.05)�͈̔́�0.15
	float mouse_sensitive = 0.1;
private:

};

