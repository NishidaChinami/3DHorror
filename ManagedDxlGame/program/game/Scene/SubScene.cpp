#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../Manager/Manager.h"
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
//-------------------Scene file------------------------//
#include"SubScene.h"
//-------------------GameObject file------------------------//
#include"PlayScene.h"
#include"../GameObject/Character/Player/Player.h"
//-------------------UI file------------------------//
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"

SubScene::SubScene(std::shared_ptr<Factory> factory, std::shared_ptr<Mediator> mediator) :m_factory(factory), m_mediator(mediator)
{
	//�`���[�g���A���Ŏg���f�[�^�̃C���X�^���X����
	m_tutorial_date.emplace_back("WASD�L�[�ňړ�", eKeys::KB_W, false);
	m_tutorial_date.emplace_back("Shift�ő���", eKeys::KB_LSHIFT, false);
	m_tutorial_date.emplace_back("Ctrl�ł��Ⴊ��", eKeys::KB_LCONTROL, true);
	m_tutorial_date.emplace_back("TAB�Ŏ��������݂�", eKeys::KB_TAB, true);
	m_tutorial_date.emplace_back("SPACE�Ń��C�g������", eKeys::KB_SPACE, true);

}

SubScene::~SubScene()
{

}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void SubScene::Update(float delta_time) {
	sequence_.Update(delta_time);
}
//------------------------------------------------------------------------------------------------------------
//�`��֐�
void SubScene::Draw() {
	auto manager = GameManager::GetInstance();
	ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
	//�C�x���gUI�̕`��
	if (m_active_event) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH/2, DXE_WINDOW_HEIGHT/2, 0), EVENTUI_WIGHT, EVENTUI_HEIGHT, true, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(EVENT_FONT);
		m_factory->GetClassMessage()->MessageDraw();
	}
	//�C���x���g���[UI�̕`��
	else if (m_active_inventory) {
		SetFontSize(INVENTORY_FONT);
		m_factory->GetClassInventory()->Draw();
	}
	//�C�x���gUI���J���ĂȂ��Ƃ���UI�`��
	else {
		//��ʂ̒��S
		//SetFontSize(10);
		DrawStringEx(640, 360, -1, "�E");
		//����Ƃ��̃X�^�~�i�Q�[�W
		if (m_mediator->MGetPlayerStamina() < Player::MAXSTAMINA) {
			DrawBoxEx(DASHGAUGE_POS, m_mediator->MGetPlayerStamina() / 2, GAUGE_HEIGHT, true, -1);
		}
		
	}
	//�`���[�g���A�����̕����̕`��
	if (m_active_tutorial) {
		SetFontSize(TUTORIAL_FONT);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		cf::DrawCenterString(m_tutorial_message.c_str(),TUTORIAL_MESSEAGE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	
}
//------------------------------------------------------------------------------------------------------------
//UI�̑ҋ@���
bool SubScene::seqIdle(float delta_time) {
	if (m_active_event)sequence_.change(&SubScene::seqEventUI); 
	if (m_active_inventory)sequence_.change(&SubScene::seqInventoryUI);
	if (GameManager::GetInstance()->is_tutorial && m_active_tutorial)sequence_.change(&SubScene::seqTutorialUI);
	return true;

}
//------------------------------------------------------------------------------------------------------------
//����`���[�g���A���̃A�b�v�f�[�g
bool SubScene::seqTutorialUI(float delta_time) {
	auto sound = Sound::GetInstance();
	if (m_active_event) {
		sequence_.change(&SubScene::seqEventUI);
		m_active_tutorial = false;
		return true;
	}
	m_time_count++;
	//��������̏����R���[�`���ň�Â`��
	auto  date_index = m_tutorial_date.begin();
	while (date_index != m_tutorial_date.end()) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(20, delta_time, [&]() {
			//20�b�Ԏw����\��
			m_tutorial_message = date_index->s_mess.c_str();
			//�����̃t�F�[�h�C��
			if (m_time_count >= 255)m_time_count = 255;
			m_alpha = m_time_count;
			//�w���̃L�[�������ꂽ�玟�̎w����
			if (tnl::Input::IsKeyDownTrigger(date_index->s_key)) {
				m_time_count = 0;
				TNL_SEQ_CO_BREAK;
			}
		});
		TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {
			//�����̃t�F�[�h�A�E�g
			m_alpha = 255 - m_time_count * 3;
			if (m_time_count >= 255)m_time_count = 255;
		});
		TNL_SEQ_CO_TIM_YIELD_RETURN(30, delta_time, [&]() {
			if (m_mediator->MGetLightParam() == date_index->s_light_flug) TNL_SEQ_CO_BREAK;
		});
		date_index++;
		if (date_index == m_tutorial_date.end()) {
			m_tutorial_message = { "" };
			m_active_tutorial = false;
			//�`���[�g���A���̕����\���I��
			sequence_.change(&SubScene::seqIdle);
			return true;
		}
	}
	TNL_SEQ_CO_END;
	return true;
}
//------------------------------------------------------------------------------------------------------------
//�C�x���gUI�̍X�V
bool SubScene::seqEventUI(float delta_time) {
	auto manager = GameManager::GetInstance();
	//�E�N���b�N����Ƒҋ@��Ԃɖ߂�
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		m_active_event = false;
		sequence_.change(&SubScene::seqIdle);
		if (m_mediator->MGetTitleType() == 0) {
			manager->ChangeScene(std::make_shared<PlayScene>());
			manager->is_tutorial = false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------------------------------------
//�C���x���g���[�̍X�V
bool SubScene::seqInventoryUI(float delta_time) {
	if (!m_active_inventory)sequence_.change(&SubScene::seqIdle);
	return true;
}


