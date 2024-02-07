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
	//�X�V����
	void Update();
	//�t�H���g�̎��
	enum class FontName {
		NORMAL,
		HORROR,
		OPTION,
		NONE
	};
	//��ʂ̖��邳
	float screen_bright = 255;
	//���̑傫��
	float sound_volume = 255;
	//�}�E�X�̊��x(0.2~0.05)�͈̔�
	float mouse_sensitive = 0.1;
	//�����̑傫��
	int font_size = 0;
	//�t�H���g�^�C�v
	FontName font = FontName::NONE;
private:
	OptionParam(){}
	//��t���[���O�̃t�H���g�T�C�Y
	int prev_font_size = 0;
	//��t���[���O�̃t�H���g�^�C�v
	FontName prev_font = FontName::NONE;
};

