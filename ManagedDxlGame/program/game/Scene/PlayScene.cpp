#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
#include"../Manager/Manager.h"
//-------------------Scene file------------------------//
#include"PlayScene.h"
#include"ResultScene.h"
#include"SubScene.h"
#include"OptionScene.h"
//-------------------GameObject file------------------------//
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/GameObject.h"
#include"../GameObject/Collision/Collision.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/Stage/StageParts.h"
#include"../GameObject/Stage/BackGroudStage.h"
//-------------------UI file------------------------//
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"
#include"../Effect/Light/Fluorescent.h"


PlayScene::PlayScene() {
	//空間の初期設定
	SetFogEnable(true);
	SetFogColor(0, 0, 0);
	SetBackgroundColor(0, 0, 0);
	SetFogStartEnd(500.0f, 1500.0f);
	SetLightDifColor(GetColorF(0.0f, 0.0f, 0.0f, 0));

	//画像の読み込み
	m_gameover_gpc_hdl = LoadGraph("graphics/death.png");
	//インスタンス生成
	m_factory = std::make_shared<Factory>();
	m_collision = std::make_shared<Collision>();
	m_player = m_factory->GetClassPlayer();
	m_subscene = std::make_shared<SubScene>(m_factory, m_factory->GetClassMediator());
	m_option = std::make_shared<OptionScene>(screen_efct);
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	m_factory->AddMainObject();
	//スクリーンエフェクトのレベルとぼかしの機能をオンにする
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL | dxe::ScreenEffect::fAdoption::BLUR);
	//サブシーンと設定シーンを子クラスに追加
	AddChild(m_subscene);
	AddChild(m_option);
	//当たり判定の関数呼び出し
	CollisionFuc();
	//BGM再生
	Sound::GetInstance()->Sound2DPlay("NEXT", DX_PLAYTYPE_BACK);
	Sound::GetInstance()->SoundStop("TUTORIAL");

}

PlayScene::~PlayScene() {
	DeleteGraph(m_gameover_gpc_hdl);
	Sound::GetInstance()->SoundStop("GAMEBGM");
	Sound::GetInstance()->SoundStop("CHASE");
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void PlayScene::Update(float delta_time) {
	//画面の明るさを変更
	screen_efct->setLevelAfterMax(OptionParam::GetInstance()->screen_bright);
	PlayBGM();
	sequence_.Update(delta_time);
	
	//設定画面開いたとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		m_option->setShowOption(true);
		sequence_.change(&PlayScene::seqOpenUI);
	}
	//カメラが有効かどうか
	m_factory->GetClassCamera()->setCameraActive(m_subscene->getBoolInventory());
	//インベントリーを開く
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		Sound::GetInstance()->Sound2DPlay("INVENTORY", DX_PLAYTYPE_BACK);
		m_subscene->getBoolInventory() == false ? m_subscene->setBoolInventory(true) : m_subscene->setBoolInventory(false);
	}
	//子クラスアップデート
	for (auto child : m_child_list) {
		child->Update(delta_time);
	}
	//全当たり判定を検知
	for (auto li : m_collision->intersect_list_) {
		if (tnl::IsIntersectAABB(li.a_->mesh->pos_, li.a_->GetObjectSize(), li.b_->mesh->pos_, li.b_->GetObjectSize())) {
			li.intersected_call_(li.a_, li.b_);
		}
	}
	
	
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void PlayScene::Draw() {
	SetFontSize(16);
	ChangeFont("Hina Mincho", DX_CHARSET_DEFAULT);
	//メインゲームの描画
	screen_efct->renderBegin();
	m_factory->GetClassBackGroudStage()->MainStageDraw(m_factory->GetClassCamera());

	for (auto obj : m_factory->GetClassObj()) {
		obj->Draw(m_factory->GetClassCamera());
	}
	for (auto child : m_child_list) {
		child->Draw();
	}
	auto manager = GameManager::GetInstance();
	if (manager->is_switch) {
		//ゲームオーバーの描画
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1, 0, m_gameover_gpc_hdl, true);
		//カメラの回転を切る
		m_factory->GetClassCamera()->setCameraActive(true);
	}
	screen_efct->renderEnd();
	
}

//------------------------------------------------------------------------------------------------------------
//BGMの再生
void PlayScene::PlayBGM() {
	auto sound = Sound::GetInstance();

	if (m_factory->GetClassMediator()->MGetChaseState()) {
		if (!sound->SoundPlaying("CHASE")) {
			sound->Sound2DPlay("CHASE");
			sound->SoundStop("GAMEBGM");
		}
	}
	else if (!sound->SoundPlaying("GAMEBGM")) {
		sound->Sound2DPlay("GAMEBGM");
		sound->SoundStop("CHASE");
	}
	
}

//------------------------------------------------------------------------------------------------------------
//ゲームプレイ状態
bool PlayScene::seqMainGame(float delta_time) {
	m_factory->GetClassCamera()->GameCameraUpdate(m_factory->GetClassMediator());
	if (m_factory->GetClassMediator()->MGetReadArticle()) {
		sequence_.change(&PlayScene::seqOpenUI);
		m_subscene->setBoolEvent(true);
	}
	
	for (auto obj : m_factory->GetClassObj()) {
		obj->Update(delta_time);
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------
//設定やインベントリーを開いた状態
bool PlayScene::seqOpenUI(float delta_time) {
	if (!m_option->getShowOption()&& !m_subscene->getBoolEvent()) {
		sequence_.change(&PlayScene::seqMainGame);
		//記事フラグをオフにしておく
		m_factory->GetClassMediator()->MSetReadArticle(false);
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------
//当たり判定のペア設定と判定後の処理を決める関数
void PlayScene::CollisionFuc() {
	//プレイヤーと壁
	m_collision->registIntersectedProcess<Player, StageWall>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {
			std::shared_ptr<Player>pl = std::dynamic_pointer_cast<Player>(a);
			std::shared_ptr<StageWall>wall = std::dynamic_pointer_cast<StageWall>(b);
			//補正処理
			pl->StageCorrection(wall);
		});
	//Enemyとプレイヤー
	m_collision->registIntersectedProcess<Player, Enemy>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {
			std::shared_ptr<Player>pl = std::dynamic_pointer_cast<Player>(a);
			std::shared_ptr<Enemy>enm = std::dynamic_pointer_cast<Enemy>(b);
			auto manager = GameManager::GetInstance();
			auto sound = Sound::GetInstance();
			//ゲームクリアのフラグをオフ
			manager->can_clear = false;
			if (!manager->is_switch) {
				//各ゲームオーバーの処理へ
				pl->GameoverEvent();
				enm->GameoverEvent();
				sound->Sound2DPlay("DEATH", DX_PLAYTYPE_BACK);
				//リザルトシーンに切り替える
				manager->ChangeScene(std::make_shared<ResultScene>());
			}
			manager->is_switch = true;
		});

	//ペアを代入
	m_enemy = m_factory->GetClassEnemy();
	m_collision->registPairObject<Player, Enemy>(m_player, m_enemy);
	m_stagewall = m_factory->GetClassStageWall();
	auto w = m_stagewall.begin();
	while (w != m_stagewall.end()) {
		m_collision->registPairObject<Player, StageWall>(m_player, *w);
		w++;
	}

}
