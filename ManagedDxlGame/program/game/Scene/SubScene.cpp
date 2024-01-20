#include "../dxlib_ext/dxlib_ext.h"
#include"SubScene.h"
#include"../Mylibrary/Conversion.h"
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"

SubScene::~SubScene()
{
}

void SubScene::Update(float delta_time) {
	sequence_.Update(delta_time);
}

void SubScene::Draw() {
	if (active_event) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		m_factory->GetClassMessage()->MessageDraw();
	}
	else if(active_inventory)m_factory->GetClassInventory()->Draw();
	else if (active_option) {
		DrawStringEx(200, 299, -1, "�ݒ���");
	}
	else {
		DrawStringEx(640, 360, -1, "+");
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {
			DrawBoxEx(DASHGAUGE_POS, m_mediator->MGetPlayerStamina(), GAUGE_HEIGHT, true, -1);
		}
	}
	//�`���[�g���A�����̕����̕`��
	if (active_tutorial) {
		cf::DrawCenterString(m_tutorial_message.c_str(),TUTORIAL_MESSEAGE);
	}
}

bool SubScene::seqIdle(float delta_time) {
	if (active_option)sequence_.change(&SubScene::seqSettingUI);
	if (active_event)sequence_.change(&SubScene::seqEventUI);
	if (active_inventory)sequence_.change(&SubScene::seqInventoryUI);
	return true;
}
//����Ɉ��Ăяo��
bool SubScene::seqTutorialUI(float delta_time) {
	//�R���[�`���p
	while (1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "WASD�L�[�ňړ��@Shift�ő���" };

			if (tnl::Input::IsKeyDown(eKeys::KB_W) ||
				tnl::Input::IsKeyDown(eKeys::KB_S) ||
				tnl::Input::IsKeyDown(eKeys::KB_A) ||
				tnl::Input::IsKeyDown(eKeys::KB_D))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "Ctrl�ł��Ⴊ��" };
			if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL))TNL_SEQ_CO_BREAK;
		});

		TNL_SEQ_CO_TIM_YIELD_RETURN(50, delta_time, [&]() {
			m_tutorial_message = { "�����Ђ낤" };
			if (m_mediator->MGetLightParam())TNL_SEQ_CO_BREAK;
		});


		//���C�g��Get�������ǂ���
		
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "TAB�Ŏ��������݂�" };
			if (tnl::Input::IsKeyDown(eKeys::KB_TAB))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			m_tutorial_message = { "Space�Ń��C�g������" };
			if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))TNL_SEQ_CO_BREAK;
			});

		TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
			m_tutorial_message = { "" };
				TNL_SEQ_CO_BREAK;
			
		});
		//�`���[�g���A���̕����\���I��
		sequence_.change(&SubScene::seqIdle);
		
	}
	TNL_SEQ_CO_END;
	return true;
}

//Escape�������ꂽ��Ăяo���A�C���x���ƃ��[��Ta���Ă΂ꂽ��Ăяo��
bool SubScene::seqSettingUI(float delta_time) {
	//���͂̓}�E�X�ňړ������𑪒肵�A����ɂ������l�ɕω�
	// �o�[�̐��l���ۂ̉��ʂ̐��l�ɐݒ�
	//�X�^�[�g�֖߂�Ńu�[���l�ω�
	
	//�V�[�g�Q��
	//�������
	if (!active_option)sequence_.change(&SubScene::seqIdle);
	return true;
}

bool SubScene::seqEventUI(float delta_time) {
	
	//item����̒ʒm�ɂ��A�`��
	if (tnl::Input::IsMouseDown(eMouse::LEFT))sequence_.change(&SubScene::seqIdle);
	return true;
}

bool SubScene::seqInventoryUI(float delta_time) {
	if (!active_inventory)sequence_.change(&SubScene::seqIdle);
	return true;
}

//eventUI���Ăяo���t���O�iMessage�������ł������ȁj
//item�Ƃ��ŌĂяo��
//void SubScene::SetEvnetNotify(bool notice, int title) {
//	m_event_notify = notice;
//	m_message->ChangeStory(title);
//
//}