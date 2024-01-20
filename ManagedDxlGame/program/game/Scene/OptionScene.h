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
private:
	//�I����ʗp�̃e���v���[�g
	tnl::Sequence<OptionScene> sequence_ = tnl::Sequence<OptionScene>(this, &OptionScene::seqOption);
	bool seqOption(float delta_time);
	bool seqIdle(float delta_time);
	const std::string MENU_LETTER[3] = { "�������","�ݒ�","�Q�[���ɖ߂�"};
	const std::string MENU_SELECT[3] = { "����","��ʂ̖��邳","�}�E�X���x"};

	bool active_option = false;
	//true�̎���������@false�̂Ƃ��͐ݒ�
	bool menu = false;
	//�w�i�n���h��
	int option_back_gpc;
	int select_gpc;
};

