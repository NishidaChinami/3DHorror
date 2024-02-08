#include "../dxlib_ext/dxlib_ext.h"
//-------------------Manager file------------------------//
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
//-------------------Scene file------------------------//
#include"TutorialScene.h"
#include"SubScene.h"
#include"OptionScene.h"
//-------------------GameObject file------------------------//
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/GameObject.h"
#include"../GameObject/Collision/Collision.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/StageWall.h"
#include"../GameObject/Stage/BackGroundStage.h"
//-------------------UI file------------------------//
#include"../UI/OptionParam.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"
#include"../Effect/Particle/GameParticle.h"



TutorialScene::TutorialScene()
{
	//空間の初期設定
	SetFogEnable(false);
	ChangeLightTypeDir(VGet(-1.0f, -0.5f, 0.0f));
	SetLightPosition(cf::ConvertToV3(tnl::Vector3(0,1800,0)));
	SetLightDifColor(GetColorF(0.2f, 0.2f, 0.2f, 0));
	SetBackgroundColor(32, 32, 32);

	//インスタンス生成
	m_factory = std::make_shared<Factory>();
	m_collision = std::make_shared<Collision>();
	m_shadow = std::make_shared<dxe::ShadowMap>(dxe::ShadowMap::eSize::S2048);
	m_player = m_factory->GetClassPlayer();
	m_subscene = std::make_shared<SubScene>(m_factory, m_factory->GetClassMediator());
	m_option = std::make_shared<OptionScene>(screen_efct);
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	particle = std::make_shared<GameParticle>();

	m_factory->AddTutorialObject();
	//スクリーンエフェクトのレベルとぼかしの機能をオンにする
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL);
	//サブシーンと設定シーンを子クラスに追加
	AddChild(m_subscene);
	AddChild(m_option);
	//当たり判定の関数呼び出し
	CollisionFunc();
	//BGM再生
	Sound::GetInstance()->Sound2DPlay("RAIN");

}

TutorialScene::~TutorialScene()
{
	Sound::GetInstance()->SoundStop("RAIN");
	Sound::GetInstance()->SoundStop("TUTORIAL");
}
//------------------------------------------------------------------------------------------------------------
//更新処理
void TutorialScene::Update(float delta_time) {
	//画面の明るさを変更
	screen_efct->setLevelAfterMax(OptionParam::GetInstance()->screen_bright);
	sequence_.Update(delta_time);
	//設定画面開いたとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		m_option->setShowOption(true);
		sequence_.change(&TutorialScene::seqOpenUI);
	}
	//カメラが有効かどうか
	m_factory->GetClassCamera()->setCameraActive(m_subscene->getBoolInventory());
	//インベントリーを開く
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		m_subscene->getBoolInventory() == false ? m_subscene->setBoolInventory(true) : m_subscene->setBoolInventory(false);
	}
	for (auto child : m_child_list) {
		child->Update(delta_time);
	}
	
	//全当たり判定を検知
	for (auto li : m_collision->m_intersect_list) {
		if (tnl::IsIntersectAABB(li.a_->mesh->pos_, li.a_->GetObjectSize(), li.b_->mesh->pos_, li.b_->GetObjectSize())) {
			li.m_intersected_call(li.a_, li.b_);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void TutorialScene::Draw() {
	SetFontSize(18);
	ChangeFont("Hina Mincho", DX_CHARSET_DEFAULT);
	//シャドウマップの準備
	m_shadow->reserveBegin();
	for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
		obj_t->mesh->reserveShadow();
	}
	for (auto stage_mesh : m_factory->GetClassBackGroundStage()->getMesh()) {
		stage_mesh->reserveShadow();
	}
	m_shadow->reserveEnd();
	//シャドウマップでの描画開始
	screen_efct->renderBegin();
	m_shadow->renderBegin();

	m_factory->GetClassBackGroundStage()->TutorialStageDraw(m_factory->GetClassCamera());
	particle->Draw(m_factory->GetClassCamera());
	for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
		obj_t->Draw(m_factory->GetClassCamera());
	}
	m_shadow->renderEnd();

	
	for (auto child : m_child_list) {
		child->Draw();
	}
	screen_efct->renderEnd();

}

//------------------------------------------------------------------------------------------------------------
//当たり判定のペア設定と判定後の処理を決める関数
void TutorialScene::CollisionFunc()
{
	//壁とプレイヤーの衝突後処理
	m_collision->registIntersectedProcess<Player, StageWall>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {
			std::shared_ptr<Player>pl = std::dynamic_pointer_cast<Player>(a);
			std::shared_ptr<StageWall>wall = std::dynamic_pointer_cast<StageWall>(b);
			//補正処理
			pl->StageCorrection(wall);
		});
	//ペアを代入
	m_stagewall = m_factory->GetClassStageTutorial();
	auto w = m_stagewall.begin();
	while (w != m_stagewall.end()) {
		m_collision->registPairObject<Player, StageWall>(m_player, *w);
		w++;
	}
}

//------------------------------------------------------------------------------------------------------------
//ゲームプレイ状態
bool TutorialScene::seqMainGame(float delta_time)
{
	m_factory->GetClassCamera()->GameCameraUpdate(m_factory->GetClassMediator());
	//記事を読むフラグがたったらサブシーンのイベントUIを呼ぶ
	if (m_factory->GetClassMediator()->MGetReadArticle()) {
		sequence_.change(&TutorialScene::seqOpenUI);
		m_subscene->setBoolEvent(true);
	}
	for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
		obj_t->Update(delta_time);
	}
	if (m_factory->GetClassMediator()->MGetLightParam()) {
		//skyboxの自己発光色を変更
		static float time_sky = m_factory->GetClassMediator()->MGetSkyEmissive().y;
		static float time_light = 1.0f;
		time_light -= 0.01f;
		time_sky -= 0.001f;
		if (time_sky <= 0) time_sky = 0;
		if (time_light <= 0) time_light = 0;
		tnl::Vector3 param = { m_factory->GetClassMediator()->MGetSkyEmissive().x,time_sky,time_sky };
		m_factory->GetClassMediator()->MSetSkyEmissive(param);
		//ディレクショナルライトの色の変更
		SetLightDifColor(GetColorF(1.0f, time_light, time_light, 1.0f));
		SetLightDifColor(GetColorF(1.0f, time_light, time_light, 1.0f));
	}

	return true;
}
//------------------------------------------------------------------------------------------------------------
//設定やインベントリーを開いた状態
bool TutorialScene::seqOpenUI(float delta_time)
{
	if (!m_option->getShowOption() && !m_subscene->getBoolEvent()) {
		sequence_.change(&TutorialScene::seqMainGame);
		//記事フラグをオフにしておく
		m_factory->GetClassMediator()->MSetReadArticle(false);
	}
	return true;
}
