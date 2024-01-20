#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	//�v���C�V�[���̍X�V�֐�
	void Update(float delta_time)override;
	//�v���C�V�[���̕`��֐�
	void Draw()override;			
	TNL_CO_SEQUENCE(TitleScene, &TitleScene::seqTitle);
private:
	//�V�[���J�ڗp�̃e���v���[�g
	tnl::Sequence<TitleScene> sequence_ = tnl::Sequence<TitleScene>(this, &TitleScene::seqTitle);
	//���ʉ�ʂ܂��̓X�^�[�g��ʂɖ߂�
	bool seqTitle(float delta_time);

	//�^�C�g���̔w�i�̃O���t�B�b�N�n���h��
	int title_gpc_hdl = 0;
	//����ǂݍ��݂̕`��n���h��
	int title_movie_hdl;
	//����Đ��p�̉摜�n���h��
	int title_screen_hdl;	

	//�^�C�g���̕����̃T�C�Y
	const float TITLE_FONT_SIZE = 40;
	//���j���[�̕����̃T�C�Y
	const float MENU_FONT_SIZE = 30;
	//�^�C�g���̕����̔z��
	const static int BUTTON_NUM = 2;
	//�^�C�g���̕�����
	const static int TITLE_NUM = 5;

	//�^�C�g������
	const std::string TITLE[TITLE_NUM] = { "��","�|","��","��","��"};

	//�^�C�g���̑I������
	const std::string START_BUTTON[BUTTON_NUM] = { "�Q�[�����n�߂�","�I�v�V����" };
	//�������\��������������ϐ�
	int m_letter_count = 0;			
	//�S�p�̂P�����̑傫��
	const int FULLWIGHT = 2;
	//�t�F�[�h�̑��x�ϐ�
	float trans_time = 5.0f;
	//���߂̕ϐ�
	int alpha = 0;
};

