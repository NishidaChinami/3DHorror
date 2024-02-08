#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../Manager/Manager.h"
//-------------------Scene file------------------------//
#include"ResultScene.h"
#include"PlayScene.h"
#include"TitleScene.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"


ResultScene::ResultScene()
{
	//背景の読み取り
	m_deathgpc_hdl = LoadGraph("graphics/horrortegami.jpg");
	m_cleargpc_hdl = LoadGraph("graphics/22443712.jpg");
	auto mgr = GameManager::GetInstance();
	//クリアかゲームオーバーかで表示する文字と背景を変更
	if (mgr->can_clear) {
		letter = CLEAR;
		m_background_hdl = m_cleargpc_hdl;
		////BGMとクリア音の再生
		Sound::GetInstance()->Sound2DPlay("CLEAR", DX_PLAYTYPE_BACK);
	}
	else {
		letter = DEATH;
		m_background_hdl = m_deathgpc_hdl;
	}
	//BGMの再生
	Sound::GetInstance()->Sound2DPlay("END");
	//フォント
	ChangeFont("Hina Mincho", DX_CHARSET_DEFAULT);
}

ResultScene::~ResultScene()
{
	Sound::GetInstance()->SoundStop("END");
	DeleteGraph(m_deathgpc_hdl);
	DeleteGraph(m_cleargpc_hdl);
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void ResultScene::Update(float delta_time)
{
	auto mgr = GameManager::GetInstance();
	//リザルトに飛ぶためのトリガーをオフにする
	mgr->is_switch = false;
	//選択項目を選択したときの処理
	if (cf::IntersectMouse(TITLE_POS, LETTER_SIZE)) {
		//タイトルに戻る
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
			Sound::GetInstance()->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
			mgr->ChangeScene(std::make_shared<TitleScene>());
		}
	}
	if (cf::IntersectMouse(REPLAY_POS, LETTER_SIZE)) {
		//もう一度プレイ
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
			Sound::GetInstance()->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
			mgr->ChangeScene(std::make_shared<PlayScene>());
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void ResultScene::Draw()
{
	//カーソル表示
	SetMouseDispFlag(true);
	int color_title = 0;
	int color_restart = 0;
	//文字とカーソルが当たっているときに色を変更する
	color_title = (cf::IntersectMouse(TITLE_POS, LETTER_SIZE)) ? -1 : 0x88888888;
	color_restart = (cf::IntersectMouse(REPLAY_POS, LETTER_SIZE))? -1: 0x88888888;
	SetFontSize(RESULT_FONT_SIZE);
	//文字と背景の描画
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1, 1, m_background_hdl, true);
	cf::DrawCenterString(letter.c_str(), CENTER_POS);
	SetFontSize(SELECT_FONT_SIZE);
	cf::DrawCenterString(SERECT[0].c_str(), TITLE_POS, color_title);
	cf::DrawCenterString(SERECT[1].c_str(), REPLAY_POS, color_restart);
	
}
