#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class OptionScene;

//-------------------------------------------------------------------------------------------------//
//�^�C�g���V�[���N���X
//-------------------------------------------------------------------------------------------------//
class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	//�v���C�V�[���̍X�V�֐�
	void Update(float delta_time)override;
	//�v���C�V�[���̕`��֐�
	void Draw()override;	
	//����Đ��R���[�`��
	TNL_CO_SEQUENCE(TitleScene, &TitleScene::seqTitle);
	//�q�N���X�ǉ�
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}
private:
	//�V�[���J�ڗp�̃V�[�P���X
	tnl::Sequence<TitleScene> sequence_ = tnl::Sequence<TitleScene>(this, &TitleScene::seqTitle);
	bool seqTitle(float delta_time);//����Đ��̃R���[�`�����񂷃V�[�P���X

	//�^�C�g���̔w�i�̃O���t�B�b�N�n���h��
	int m_title_gpc_hdl = 0;
	//����ǂݍ��݂̕`��n���h��
	int m_title_movie_hdl= 0;
	//����Đ��p�̉摜�n���h��
	int m_title_screen_hdl = 0;	

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	//�e�N���X�̃��X�g��p��
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//�q�N���X�ł���I�v�V�����V�[���N���X�̃��X�g
	std::shared_ptr<OptionScene>m_option;
	//----------------------�萔------------------------//
	//�^�C�g���̕����̃T�C�Y
	const float TITLE_FONT_SIZE = 40;
	//���j���[�̕����̃T�C�Y
	const float MENU_FONT_SIZE = 30;
	//�^�C�g���̕����̔z��
	const static int BUTTON_NUM = 4;
	//�^�C�g���̕�����
	const static int TITLE_NUM = 5;

	//�^�C�g������
	const std::string TITLE[TITLE_NUM] = { "��","�|","��","��","��"};
	const tnl::Vector3 TITLE_SELECT_POS = { DXE_WINDOW_WIDTH / 2,500,0 };
	//�����̓����蔻��̃T�C�Y
	const tnl::Vector3 SELECT_SIZE = { 200,50, 0 };

	//�I�����ڂ̕����̐F�̔z��
	int color_index[BUTTON_NUM] = { 0 };
	//�^�C�g���̑I������
	const std::string START_BUTTON[BUTTON_NUM] = { "�Q�[�����n�߂�","�`���[�g���A��","�I�v�V����","�Q�[������߂�"};	
	//�S�p�̂P�����̑傫��
	const int FULLWIGHT = 2;
	//�t�F�[�h�̑��x�ϐ�
	const float TRANS_TIME = 5.0f;

};

