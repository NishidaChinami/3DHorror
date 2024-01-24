#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../dxlib_ext/gui/dxlib_ext_gui_value_slider.h"
#include"BaseScene.h"

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

	void BarDraw();


	void SetBoolOption(bool option) { m_active_option = option; }
	bool GetBoolOption() { return m_active_option; }
	TNL_PROPERTY(float, Volume, m_volume);
	TNL_PROPERTY(float, Bright, m_bright);
	TNL_PROPERTY(float, Sensitive, m_sensitivity);

private:

	const static int MENU_NUM = 4;
	const static int SELECT_NUM = 3;
	const std::string MENU_LETTER[MENU_NUM] = { "�������","�ݒ�","�Q�[���ɖ߂�","�Q�[������߂�"};
	const std::string MENU_SELECT[SELECT_NUM] = { "����","��ʂ̖��邳","�}�E�X���x"};

	bool m_active_option = false;
	//true�̎���������@false�̂Ƃ��͐ݒ�
	bool m_menu = false;
	//�w�i�n���h��
	int m_option_back_gpc = 0;
	//�L�[�o�C���h�̃n���h��
	int m_keybind_hdl = 0;
	//�e�ݒ�̕ϐ��i�����W�j
	float m_volume = 255;;
	float m_bright = 255;;
	float m_sensitivity = 0.1;

	const float OPTION_WIDTH = 720;
	const float OPTION_HEIGHT = 460;
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	const float RADIUS = 10;

	const tnl::Vector3 MENU_POS = { 250,360,0 };
	const tnl::Vector3 SELECT_POS = {490,220,0};
	const tnl::Vector2i PROGRESS_BAR_VOLUME = { 640,220};
	const tnl::Vector2i PROGRESS_BAR_BRIGHT = { 640,320};
	const tnl::Vector2i PROGRESS_BAR_SENSITIVITY = { 640,420};

	const tnl::Vector3 MENU_SIZE = { 100,50,0 };

	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_volume;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_bright;
	Shared<dxe::GuiValueSlider< OptionScene, float >>gui_sensitive;
};

