#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//

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
	//画像ハンドルの読み込み
	m_title_gpc_hdl = LoadGraph("graphics/nc296749.jpg");
	//タイトル動画読み込み
	m_title_movie_hdl = LoadGraph("movie/ホラー風ノイズ_無料版.mp4");
	//動画の画像サイズを取得
	tnl::Vector2i size = { 0,0 };
	GetGraphSize(m_title_movie_hdl, &size.x, &size.y);
	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	m_title_screen_hdl = MakeScreen(size.x, size.y, TRUE);
	//ムービーの再生
	PlayMovieToGraph(m_title_movie_hdl, DX_MOVIEPLAYTYPE_NORMAL);
	//スクリーンエフェクトの生成
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	//画面の明るさの調整するエフェクトのフラグをオン
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL);

	//オプションシーンを子クラスに設定
	m_option = std::make_shared<OptionScene>(screen_efct);
	AddChild(m_option);
	//Opサウンド再生
	auto sound = Sound::GetInstance();
	sound->Sound2DPlay("OP");
}

TitleScene::~TitleScene()
{
	//Opサウンド再生終了
	Sound::GetInstance()->SoundStop("OP");
	DeleteGraph(m_title_gpc_hdl);
	DeleteGraph(m_title_screen_hdl);
	DeleteGraph(m_title_movie_hdl);

}
//------------------------------------------------------------------------------------------------------------
//更新処理
void TitleScene::Update(float delta_time) {
	sequence_.Update(delta_time);
	
	auto manager = GameManager::GetInstance();
	auto sound = Sound::GetInstance();
	//選択したとき
	for (int i = 0; i < BUTTON_NUM; i++) {
		tnl::Vector3 pos = { TITLE_SELECT_POS.x, TITLE_SELECT_POS.y + i * 50, 0 };
		//マウスと文字が当たっていったら色を変更
		color_index[i] = cf::IntersectMouse(pos, SELECT_SIZE) ? -1 : 0x88888888;
		if (cf::IntersectMouse(pos, SELECT_SIZE)) {
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				sound->Sound2DPlay("SELECT", DX_PLAYTYPE_BACK);
				switch (i)
				{
					//チュートリアルから
					case 0: {
						manager->ChangeScene(std::make_shared<PlayScene>());
						manager->is_tutorial = false;
						break;
					}
					//メインゲームから
					case 1: {
						manager->ChangeScene(std::make_shared<TutorialScene>());
						manager->is_tutorial = true;
						break;
					}
					//オプション画面の表示
					case 2: {m_option->setShowOption(true); break; }
					//ゲームをやめる
					case 3: {
						DxLib_End();
						break;
					}

				}
			}
		}
	}
	//子クラスのアップデート
	for (auto child : m_child_list) {
		child->Update(delta_time);
	}

}
//------------------------------------------------------------------------------------------------------------
//描画処理
void TitleScene::Draw() {
	//透過の値を時間経過で変化
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	SetFontSize(TITLE_FONT_SIZE);
	ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	//タイトル文字の描画
	for (int i = 0; i < TITLE_NUM; i++) {
		DrawStringEx(1100 - i * 10, 100 + i * 50, -1, "%s", TITLE[i].c_str());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//タイトルの文字が描画されたらタイトルの選択項目の表示
	if (alpha >= 200) {
		SetFontSize(MENU_FONT_SIZE);
		ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
		for (int i = 0; i < BUTTON_NUM; i++) {
			cf::DrawCenterString(START_BUTTON[i].c_str(), tnl::Vector3(TITLE_SELECT_POS.x, TITLE_SELECT_POS.y + i * 50, 0), color_index[i]);
		}
	}
	//子クラスの描画アップデート
	for (auto child : m_child_list) {
		child->Draw();
	}
}
//------------------------------------------------------------------------------------------------------------
//動画再生
bool TitleScene::seqTitle(float delta_time) {
	//背景の描画
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// 動画再生　コルーチンで無限再生
	while (1) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(30, delta_time, [&]() {

			GraphFilterBlt(m_title_movie_hdl, m_title_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
			DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, m_title_screen_hdl, TRUE);

		});
	}
	TNL_SEQ_CO_END;
	
	return true;
}

