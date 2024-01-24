#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"../Manager/Manager.h"
#include"../Effect/Sound/Sound.h"


TitleScene::TitleScene()
{
	//�摜�n���h���̓ǂݍ���
	title_gpc_hdl = LoadGraph("graphics/nc296749.jpg");
	//�^�C�g������ǂݍ���
	title_movie_hdl = LoadGraph("movie/�z���[���m�C�Y_������.mp4");
	//����̉摜�T�C�Y���擾
	int size_x = 0;
	int size_y = 0;
	GetGraphSize(title_movie_hdl, &size_x, &size_y);
	//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
	title_screen_hdl = MakeScreen(size_x, size_y, TRUE);
	PlayMovieToGraph(title_movie_hdl, DX_MOVIEPLAYTYPE_NORMAL);
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	screen_efct->loadStatus("screen_effect.bin");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float delta_time) {
	sequence_.Update(delta_time);
}

void TitleScene::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	for (int i = 0; i < TITLE_NUM; i++) {
		//�ꕶ�����ǉ�����Ă����Hvector��
		DrawStringEx(1100 - i * 10, 100 + i * 50, -1, "%s", TITLE[i].c_str());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//�I���̕`��
	alpha = (sequence_.getProgressTime() / trans_time * 255.0f);
	DrawStringEx(100, 100, -1, "%d", alpha);

	if (alpha >= 200) {
		SetFontSize(MENU_FONT_SIZE);
		for (int i = 0; i < BUTTON_NUM; i++) {
			cf::DrawCenterString(START_BUTTON[i].c_str(), tnl::Vector3(600, 500 + i * 50, 0));
		}
	}
	if (cf::IntersectMouse(tnl::Vector3(600, 500, 0), tnl::Vector3(200,50, 0))) {
		DrawStringEx(100, 200, -1, "�������");
		if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
			auto mgr = GameManager::GetInstance();
			mgr->ChangeScene(std::make_shared<PlayScene>());
		}
	}
}

bool TitleScene::seqTitle(float delta_time) {
	SetFontSize(TITLE_FONT_SIZE);
	ChangeFont("g_�R�~�b�N�z���[���|-����", DX_CHARSET_DEFAULT);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, title_gpc_hdl, true);
	// ����Đ�
	while (-1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(30, delta_time, [&]() {

			GraphFilterBlt(title_movie_hdl, title_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
			DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, title_screen_hdl, TRUE);

			});
	}
	TNL_SEQ_CO_END;
	
	return true;
}

//�Q�[���X�^�[�g
//

