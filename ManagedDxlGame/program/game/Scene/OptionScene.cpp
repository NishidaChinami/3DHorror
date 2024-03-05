#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../Manager/Manager.h"
#include"OptionScene.h"
#include"../UI/OptionParam.h"
#include"TitleScene.h"
#include"../Effect/Sound/Sound.h"

OptionScene::OptionScene(Shared<dxe::ScreenEffect> m_screen_efct)
{
	//�摜�̓ǂݍ���
	m_option_back_gpc = LoadGraph("graphics/PanelFrame.png");
	m_keybind_hdl = LoadGraph("graphics/keybind.png");
	//������
	auto param = OptionParam::GetInstance();
	m_volume = param->getParamVolume();
	m_bright = param->getParamBright();
	m_sensitivity = param->getParamSensitive();

	screen_efct = m_screen_efct;
}

OptionScene::~OptionScene()
{
	DeleteGraph(m_option_back_gpc);
	DeleteGraph(m_keybind_hdl);
}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void OptionScene::Update(float delta_time) {
	if (!m_active_option)return;
	auto param = OptionParam::GetInstance();
	auto sound = Sound::GetInstance();
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 50, 0 };
		color_index[i] = cf::IntersectMouse(pos, MENU_SIZE) ? -1 : 0;
		//0x88888888
		if (cf::IntersectMouse(pos, MENU_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				sound->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
				//���j���[�̑I�����̏���
				switch (i)
				{
					//�ݒ���
					case 0:m_menu = true; break;
					//�V�ѕ�
					case 1:m_menu = false; break;
					//�Q�[�����ĊJ
					case 2: {
						m_active_option = false; 
						break;
					}
					//�^�C�g���ɖ߂�
					case 3:
						if(m_title_isvalid)m_active_option = false;
						else {
							auto manager = GameManager::GetInstance();
							manager->ChangeScene(std::make_shared<TitleScene>());
						}
						break;
				}
			}
		}		
	}

	if (!m_menu) {
	//�I�v�V�����p�����[�^�[�ɑ��
		param->setParamVolume(m_volume);
		param->setParamBright(m_bright);
		param->setParamSensitive(m_sensitivity);
	}
}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void OptionScene::Draw() {
	if (!m_active_option) { return; }
	//�I�v�V������ʂ̔w�i
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DIANETER, 0, m_option_back_gpc, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(BACK_POS, OPTION_WIDTH, OPTION_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//���j���[���ڂ̕����̕`��
	SetFontSize(MENU_FONT);
	ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
	for (int i = 0; i < MENU_NUM; i++) {
		tnl::Vector3 pos = { MENU_POS.x, MENU_POS.y + i * 50,0 };
		cf::DrawCenterString(MENU_LETTER[i].c_str(), pos, color_index[i]);
	}
	if (m_menu) {
		//�������
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2 + 100, DXE_WINDOW_HEIGHT / 2, 1, 0, m_keybind_hdl, true);
	}
	else {
		//�X���C�_�[�̕`��
		BarDraw();
		//�ݒ��ʂ̑I�����ڂ̕����̕`��
		for (int i = 0; i < SELECT_NUM; i++) {
			DrawStringEx(SELECT_POS.x, SELECT_POS.y + i * 100, -1, "%s", MENU_SELECT[i].c_str());
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//�X���C�_�[�̕`��̏���
void OptionScene::BarDraw()
{
	
	if (!gui_volume) {
		gui_volume = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getVolume,
				&OptionScene::setVolume,
				PROGRESS_BAR_VOLUME,
				MIN_VOLUME,
				MAX_VOLUME,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	if (!gui_bright) {
		gui_bright = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getBright,
				&OptionScene::setBright,
				PROGRESS_BAR_BRIGHT,
				MIN_VOLUME,
				MAX_VOLUME,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	if (!gui_sensitive) {
		gui_sensitive = Shared<dxe::GuiValueSlider< OptionScene, float >>(
			new dxe::GuiValueSlider< OptionScene, float >
			(this,
				&OptionScene::getSensitive,
				&OptionScene::setSensitive,
				PROGRESS_BAR_SENSITIVITY,
				MIN_SENSITIVITY,
				MAX_SENSITIVITY,
				BAR_STRING.c_str(),
				MAX_BAR));
	}
	gui_bright->Update();
	gui_volume->Update();
	gui_sensitive->Update();
	gui_bright->draw();
	gui_volume->draw();
	gui_sensitive->draw();
}


