#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class OptionScene:public BaseScene
{
public:
	OptionScene();
	~OptionScene();
	//�V�[���̍X�V
	void Update(float delta_time)override;
	//�V�[���̕`��֐�
	void Draw()override;

	void SetBoolOption(bool option) { m_active_option = option; }
private:

	static const int MENU_NUM = 4;
	static const int SELECT_NUM = 3;
	static const int KEY_NUM = 12;
	const std::string MENU_LETTER[MENU_NUM] = { "�������","�ݒ�","�Q�[���ɖ߂�","�Q�[������߂�"};
	const std::string MENU_SELECT[SELECT_NUM] = { "����","��ʂ̖��邳","�}�E�X���x"};
	const std::string KEY_BIND[KEY_NUM] = { "W","A","S""D","Shift","Ctrl","E","Space","Esc","Tab","�}�E�X","�E�N���b�N"};
	const std::string OPERATION[KEY_NUM] = { "�O�i","���ړ�","�E�ړ�","��i","����","���Ⴊ��","�E��/���ׂ�","���C�g������","�ݒ��ʂ��J��","������������","���_�ړ�","�I��" };

	bool m_active_option = false;
	//true�̎���������@false�̂Ƃ��͐ݒ�
	bool m_menu = false;
	//�w�i�n���h��
	int m_option_back_gpc;
	//�e�ݒ�̕ϐ��i�����W�j
	float m_volume;
	float m_bright;
	float m_sensitivity;

	float m_param_index[SELECT_NUM] = {m_volume,m_bright,m_sensitivity};

	const float OPTION_WIDTH = 800;
	const float OPTION_HEIGHT = 480;
	const float BAR_WIDTH = 300;
	const float BAR_HEIGHT = 5;
	const float RADIUS = 5;

	const tnl::Vector3 MENU_POS = { 150,360,0 };
	const tnl::Vector3 KEY_BIND_POS = { 390,120,0 };
	const tnl::Vector3 OPERATION_POS = { 490,220,0 };
	const tnl::Vector3 SELECT_POS = {390,120,0};
	const tnl::Vector3 PROGRESS_BAR_VOLUME = { 490,220,0 };
	const tnl::Vector3 PROGRESS_BAR_BRIGHT = { 490,320,0 };
	const tnl::Vector3 PROGRESS_BAR_SENSITIVITY = { 490,420,0 };

	const tnl::Vector3 MENU_SIZE = { 100,50,0 };
};

