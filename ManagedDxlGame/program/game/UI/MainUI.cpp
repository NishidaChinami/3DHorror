#include "../dxlib_ext/dxlib_ext.h"
#include"MainUI.h"
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"

MainUI::MainUI(){
	m_inventory = std::make_shared<Inventory>();
	m_message = std::make_shared<Message>();
}

void MainUI::Update(float delta_time) {
	sequence_.Update(delta_time);
}

bool MainUI::seqIdle(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))sequence_.change(&MainUI::seqSettingUI);
	if(m_event_notify)sequence_.change(&MainUI::seqEventUI);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))sequence_.change(&MainUI::seqInventoryUI);
	return true;
}
//����Ɉ��Ăяo��
bool MainUI::seqTutorialUI(float delta_time) {
	//�R���[�`���p
	while (1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			DrawStringEx(100, 100, -1, "WASD�L�[�ňړ�" );
				if(tnl::Input::IsKeyDown(eKeys::KB_W) ||
					tnl::Input::IsKeyDown(eKeys::KB_S) ||
					tnl::Input::IsKeyDown(eKeys::KB_A) ||
					tnl::Input::IsKeyDown(eKeys::KB_D) )TNL_SEQ_CO_BREAK;
		});
		
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			DrawStringEx(100, 100, -1, "Ctrl�ł��Ⴊ��");
			if(tnl::Input::IsKeyDown(eKeys::KB_LCONTROL))TNL_SEQ_CO_BREAK;
		});
	}
	//���C�g��Get�������ǂ���
	//if (bool getlight) {
	//	//TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
	//		//DrawStringEx(100,100,-1,"%s",)
	//		//if (tnl::Input::IsKeyDown(eKeys::KB_TAB))TNL_SEQ_CO_BREAK;
	//		//});

	//	TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
	//		//DrawStringEx(100,100,-1,"%s",)
	//		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))TNL_SEQ_CO_BREAK;
	//	});

	//	TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {});
	//	//�g���K�[�ƂȂ铖���蔻���݂��邩���ԂŊǗ����邩
	//	sequence_.change(&MainUI::seqIdle);
	//}

	TNL_SEQ_CO_END;
	return true;
}

//Escape�������ꂽ��Ăяo���A�C���x���ƃ��[��Ta���Ă΂ꂽ��Ăяo��
bool MainUI::seqSettingUI(float delta_time) {
	//���͂̓}�E�X�ňړ������𑪒肵�A����ɂ������l�ɕω�
	// �o�[�̐��l���ۂ̉��ʂ̐��l�ɐݒ�
	//�X�^�[�g�֖߂�Ńu�[���l�ω�
	DrawStringEx(200, 299, -1, "�ݒ���");
	//�V�[�g�Q��
	//�������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))sequence_.change(&MainUI::seqIdle);
	return true;
}

bool MainUI::seqEventUI(float delta_time) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//item����̒ʒm�ɂ��A�`��
	if (tnl::Input::IsMouseDown(eMouse::LEFT))sequence_.change(&MainUI::seqIdle);
	return true;
}

bool MainUI::seqInventoryUI(float delta_time) {
	m_inventory->Draw();
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))sequence_.change(&MainUI::seqIdle);
	return true;
}

//eventUI���Ăяo���t���O�iMessage�������ł������ȁj
//item�Ƃ��ŌĂяo��
void MainUI::SetEvnetNotify(bool notice, int title) {
	m_event_notify = notice;
	m_message->ChangeStory(title);

}