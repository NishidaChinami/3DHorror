#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../dxlib_ext/gui/dxlib_ext_gui_value_slider.h"
#include"BaseScene.h"

//-------------------------------------------------------------------------------------------------//
//BaseScene�p���̃I�v�V������ʂ̃N���X
// Title��Play,TutorialScene�̎q�N���X�Ƃ��ċ@�\����
// Component�p�^�[����͂��č쐬�����B����͂��p�^�[���̍\���ɋ߂�����
//-------------------------------------------------------------------------------------------------//
class OptionScene:public BaseScene
{
public:
	OptionScene(){}
	OptionScene(Shared<dxe::ScreenEffect> m_screen_efct);
	~OptionScene();
	//�V�[���̍X�V
	void Update(float delta_time)override;
	//�V�[���̕`��֐�
	void Draw()override;
	//�X���C�_�[�̕`��֐�
	void BarDraw();
	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(bool, ShowOption, m_active_option);
	TNL_PROPERTY(float, Volume, m_volume);
	TNL_PROPERTY(float, Bright, m_bright);
	TNL_PROPERTY(float, Sensitive, m_sensitivity);
	TNL_PROPERTY(bool, TitleIsValid, m_title_isvalid);

	//�I�v�V������ʂ̕���
	const static int MENU_NUM = 4;
	const static int SELECT_NUM = 3;
private:
	//�I�v�V������ʂ��J����Ă��邩�ǂ���
	bool m_active_option = false;
	//�^�C�g����ʂ��ǂ���
	bool m_title_isvalid = false;
	//�V�ѕ����ݒ��ʂ��𕪂���t���O
	//true�̎���������@false�̂Ƃ��͐ݒ�
	bool m_menu = false;
	//�w�i�n���h��
	int m_option_back_gpc = 0;
	//�L�[�o�C���h�̃n���h��
	int m_keybind_hdl = 0;

	//�e�ݒ�̕ϐ��i�����W�j
	float m_volume = 255;
	float m_bright = 255;
	float m_sensitivity = 0.1;
	
	//�����̐F�̔z��
	int color_index[MENU_NUM] = { 0 };

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_volume;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_bright;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_sensitive;
	//----------------------�萔------------------------//
	//�I�v�V������ʂ̕���
	const std::string MENU_LETTER[MENU_NUM] = { "�������","�ݒ�","�Q�[���ɖ߂�","�Q�[������߂�" };
	const std::string MENU_SELECT[SELECT_NUM] = { "����","��ʂ̖��邳","�}�E�X���x" };
	//�I�v�V������ʂ̃{�b�N�X�̃T�C�Y
	const float OPTION_WIDTH = 720;
	const float OPTION_HEIGHT = 460;
	//�X���C�_�[�̃{�b�N�X�̃T�C�Y
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	//�܂݂̔��a
	const float RADIUS = 10;

	//�ݒ��ʂ̍��ڂ̐擪���W
	const tnl::Vector3 MENU_POS = { 250,360,0 };
	//���ʂ▾�邳���̑I�����ڂ̐擪���W
	const tnl::Vector3 SELECT_POS = { 490,220,0 };
	//�e���ڂ̃X���C�_�[�̍��W
	const tnl::Vector2i PROGRESS_BAR_VOLUME = { 640,220 };
	const tnl::Vector2i PROGRESS_BAR_BRIGHT = { 640,320 };
	const tnl::Vector2i PROGRESS_BAR_SENSITIVITY = { 640,420 };

	//�����̓����蔻��̃T�C�Y
	const tnl::Vector3 MENU_SIZE = { 200,50,0 };
	//�t�H���g�T�C�Y
	const int MENU_FONT = 18;
};

