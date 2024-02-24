#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../gm_main.h"
#include"../Manager/Manager.h"
//-------------------Scene file------------------------//
#include"TitleScene.h"
#include"PlayScene.h"
#include"OptionScene.h";
#include"TutorialScene.h"
//-------------------UI file------------------------//
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"

TitleScene::TitleScene()
{
	//画像ハンドルの読み込み
	m_title_gpc_hdl = LoadGraph("graphics/title.jpg");
	//タイトル動画読み込み
	m_title_movie_hdl = LoadGraph("movie/ホラー風ノイズ_無料版.mp4");
	//動画の画像サイズを取得
	tnl::Vector2i size = { 0,0 };
	GetGraphSize(m_title_movie_hdl, &size.x, &size.y);
	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	m_title_screen_hdl = MakeScreen(size.x, size.y, TRUE);
	//ムービーの再生
	PlayMovieToGraph(m_title_movie_hdl, DX_PLAYTYPE_LOOP);
	//スクリーンエフェクトの生成
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	//画面の明るさの調整するエフェクトのフラグをオン
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL);

	//オプションシーンを子クラスに設定
	m_option = std::make_shared<OptionScene>(screen_efct);
	AddChild(m_option);
	m_option->setTitleIsValid(true);
	//Opサウンド再生
	auto sound = Sound::GetInstance();
	sound->Sound2DPlay("OP");
	//カーソル表示
	SetMouseDispFlag(true);
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
	m_time_count += delta_time;
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
						m_option->setTitleIsValid(false);
						break;
					}
					//メインゲームから
					case 1: {
						manager->ChangeScene(std::make_shared<TutorialScene>());
						manager->is_tutorial = true;
						m_option->setTitleIsValid(false);
						break;
					}
					//オプション画面の表示
					case 2: {m_option->setShowOption(true); break; }
					//ゲームをやめる
					case 3: {
						gameEnd();
						exit(0);
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
	//動画再生
	GraphFilterBlt(m_title_movie_hdl, m_title_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, m_title_screen_hdl, TRUE);
	SetFontSize(TITLE_FONT_SIZE);
	ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	//タイトル文字の描画
	for (int i = 0; i < TITLE_NUM; i++) {
		DrawStringEx(1100 - i * 10, 100 + i * 50, -1, "%s", TITLE[i].c_str());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//タイトルの文字が描画されたらタイトルの選択項目の表示
	if (m_time_count >= 5) {
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
//背景の透過の変化　透過率が高くなる
bool TitleScene::seqMax(float delta_time) {
	//背景の描画
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	//背景描画
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, m_title_gpc_hdl, true);
	//徐々に薄く描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - alpha);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (alpha >= 255) {
		sequence_.change(&TitleScene::seqIdle);
	}
	
	return true;
}

//------------------------------------------------------------------------------------------------------------
//背景の透過の変化　透過率が小さくなる
bool TitleScene::seqMin(float delta_time)
{
	//背景の描画
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	//背景描画
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, m_title_gpc_hdl, true);
	//徐々に濃く描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, m_title_gpc_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (alpha >= 200) {
		sequence_.change(&TitleScene::seqMax);
	}

	return true;
}
//------------------------------------------------------------------------------------------------------------
//背景の透過の変化　待機状態
bool TitleScene::seqIdle(float delta_time)
{
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.8, 0, m_title_gpc_hdl, true);
	int alpha = (sequence_.getProgressTime() / TRANS_TIME * 255.0f);
	//待機時間をランダムに設定
	int rand_time = rand() % IDLE_TIME + IDLE_TIME;
	if (alpha >= rand_time) {
		sequence_.change(&TitleScene::seqMin);
	}
	return true;
}

