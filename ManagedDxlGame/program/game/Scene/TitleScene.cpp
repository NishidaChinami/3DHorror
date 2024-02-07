#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../gm_main.h"
#include"../Manager/Manager.h"
//-------------------Scene file------------------------//
#include"TitleScene.h"
#include"PlayScene.h"
#include"OptionScene.h";
#include"TurorialScene.h"
//-------------------UI file------------------------//
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"

TitleScene::TitleScene()
{
	//�摜�n���h���̓ǂݍ���
	m_title_gpc_hdl = LoadGraph("graphics/nc296749.jpg");
	//�^�C�g������ǂݍ���
	m_title_movie_hdl = LoadGraph("movie/�z���[���m�C�Y_������.mp4");
	//����̉摜�T�C�Y���擾
	tnl::Vector2i size = { 0,0 };
	GetGraphSize(m_title_movie_hdl, &size.x, &size.y);
	//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
	m_title_screen_hdl = MakeScreen(size.x, size.y, TRUE);
	//���[�r�[�̍Đ�
	PlayMovieToGraph(m_title_movie_hdl, DX_MOVIEPLAYTYPE_NORMAL);
	//�X�N���[���G�t�F�N�g�̐���
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	//��ʂ̖��邳�̒�������G�t�F�N�g�̃t���O���I��
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL);

	//�I�v�V�����V�[�����q�N���X�ɐݒ�
	m_option = std::make_shared<OptionScene>(screen_efct);
	AddChild(m_option);
	m_option->setTitleIsValid(true);
	//Op�T�E���h�Đ�
	auto sound = Sound::GetInstance();
	sound->Sound2DPlay("OP");
}

TitleScene::~TitleScene()
{
	//Op�T�E���h�Đ��I��
	Sound::GetInstance()->SoundStop("OP");
	DeleteGraph(m_title_gpc_hdl);
	DeleteGraph(m_title_screen_hdl);
	DeleteGraph(m_title_movie_hdl);
}
//------------------------------------------------------------------------------------------------------------
//�X�V����
void TitleScene::Update(float delta_time) {
	sequence_.Update(delta_time);
	
	auto manager = GameManager::GetInstance();
	auto sound = Sound::GetInstance();
	//�I�������Ƃ�
	for (int i = 0; i < BUTTON_NUM; i++) {
		tnl::Vector3 pos = { TITLE_SELECT_POS.x, TITLE_SELECT_POS.y + i * 50, 0 };
		//�}�E�X�ƕ������������Ă�������F��ύX
		color_index[i] = cf::IntersectMouse(pos, SELECT_SIZE) ? -1 : 0x88888888;
		if (cf::IntersectMouse(pos, SELECT_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				sound->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
				switch (i)
				{
					//�`���[�g���A������
					case 0: {
						manager->ChangeScene(std::make_shared<PlayScene>());
						manager->is_tutorial = false;
						m_option->setTitleIsValid(false);
						break;
					}
					//���C���Q�[������
					case 1: {
						manager->ChangeScene(std::make_shared<TutorialScene>());
						manager->is_tutorial = true;
						m_option->setTitleIsValid(false);
						break;
					}
					//�I�v�V������ʂ̕\��
					case 2: {m_option->setShowOption(true); break; }
					//�Q�[������߂�
					case 3: {
						gameEnd();
						exit(0);
						break;
					}

				}
			}
		}
	}
	//�q�N���X�̃A�b�v�f�[�g
	for (auto child : m_child_list) {
		child->Update(delta_time);
	}

}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void TitleScene::Draw() {
	//���߂̒l�����Ԍo�߂ŕω�
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	SetFontSize(TITLE_FONT_SIZE);
	ChangeFont("g_�R�~�b�N�z���[���|-����", DX_CHARSET_DEFAULT);
	//�^�C�g�������̕`��
	for (int i = 0; i < TITLE_NUM; i++) {
		DrawStringEx(1100 - i * 10, 100 + i * 50, -1, "%s", TITLE[i].c_str());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//�^�C�g���̕������`�悳�ꂽ��^�C�g���̑I�����ڂ̕\��
	if (alpha >= 200) {
		SetFontSize(MENU_FONT_SIZE);
		ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
		for (int i = 0; i < BUTTON_NUM; i++) {
			cf::DrawCenterString(START_BUTTON[i].c_str(), tnl::Vector3(TITLE_SELECT_POS.x, TITLE_SELECT_POS.y + i * 50, 0), color_index[i]);
		}
	}
	//�q�N���X�̕`��A�b�v�f�[�g
	for (auto child : m_child_list) {
		child->Draw();
	}
}
//------------------------------------------------------------------------------------------------------------
//����Đ�
bool TitleScene::seqTitle(float delta_time) {
	//�w�i�̕`��
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// ����Đ��@�R���[�`���Ŗ����Đ�
	while (true) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(30, delta_time, [&]() {
			GraphFilterBlt(m_title_movie_hdl, m_title_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
			DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, m_title_screen_hdl, TRUE);
		});
	}
	TNL_SEQ_CO_END;
	
	return true;
}

