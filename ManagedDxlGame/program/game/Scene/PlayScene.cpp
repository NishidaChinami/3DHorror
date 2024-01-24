#include "../dxlib_ext/dxlib_ext.h"
#include"PlayScene.h"
#include"../Manager/Factory.h"
#include"../Manager/Mediator.h"
#include"../Manager/Manager.h"
#include"ResultScene.h"
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/GameObject.h"
#include"../GameObject/Collision/Collision.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/Stage/StageParts.h"
#include"../GameObject/Stage/BackGroudStage.h"
#include"../Effect/Sound/Sound.h"
#include"../Effect/Light/Fluorescent.h"
#include"../UI/MainUI.h"
#include"SubScene.h"
#include"OptionScene.h"
#include"../UI/OptionParam.h"]


PlayScene::PlayScene() {
	ChangeLightTypeDir(VGet(0.2f, -1.5f, 0.0f));
	SetBackgroundColor(32, 32, 32);
	m_factory = std::make_shared<Factory>();
	m_collision = std::make_shared<Collision>(m_factory);
	m_shadow = std::make_shared<dxe::ShadowMap>(dxe::ShadowMap::eSize::S2048);
	m_player = m_factory->GetClassPlayer();
	m_subscene = std::make_shared<SubScene>(m_factory, m_factory->GetClassMediator());
	screen_efct = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	m_option = std::make_shared<OptionScene>(screen_efct);
	m_sound = std::make_shared<Sound>();
	screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL);
	//screen_efct->setAdoption(dxe::ScreenEffect::fAdoption::LEVEL | dxe::ScreenEffect::fAdoption::BLOOM);
	AddChild(m_subscene);
	AddChild(m_option);
	CollitionFuc();
}

PlayScene::~PlayScene() {

}

void PlayScene::Update(float delta_time) {
	ScreenEffect();
	PlayBGM();
	sequence_.Update(delta_time);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		m_option->SetBoolOption(true);
		sequence_.change(&PlayScene::seqOpenUI);
	}
	//これでいけるのか？
	//if(m_factory->GetClassMediator()->MSetMessage(1))sequence_.change(&PlayScene::seqSetMainGame);

	for (auto child : m_child_list) {
		child->Update(delta_time);
	}
	//全当たり判定を検知
	for (auto li : m_collision->intersect_list_) {
		if (tnl::IsIntersectAABB(li.a_->mesh->pos_, li.a_->GetObjectSize(), li.b_->mesh->pos_, li.b_->GetObjectSize())) {
			li.intersected_call_(li.a_, li.b_);
		}
	}
	m_sound->ChangeVolume();
	
}

void PlayScene::Draw() {
	
	if (m_alive_tutorial) {
		m_shadow->reserveBegin();
		for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
			obj_t->mesh->reserveShadow();
		}
		m_shadow->reserveEnd();

		//m_shadow->renderBegin();
		screen_efct->renderBegin();
		m_skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));
		m_skybox->render(m_factory->GetClassCamera());

		for (auto soil : m_factory->GetClassSoilGroudStage()) {
			soil->Draw(m_factory->GetClassCamera());
		}
		for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
			obj_t->Draw(m_factory->GetClassCamera());
		}
		screen_efct->renderEnd();
		//m_shadow->renderEnd();
	}
	else {
		screen_efct->renderBegin();
		for (auto groud : m_factory->GetClassBackGroudStage()) {
			groud->Draw(m_factory->GetClassCamera());
		}

		for (auto obj : m_factory->GetClassObj()) {
			obj->Draw(m_factory->GetClassCamera());
		}
		screen_efct->renderEnd();
	}

	for (auto child : m_child_list) {
		child->Draw();
	}
	
}

void PlayScene::PlayBGM() {
	//if (m_factory->GetClassMediator()->MGetChaseState()) {
	//	if (!m_sound->SoundPlaying("CHASE")) {
	//		m_sound->Sound2DPlay("CHASE");
	//		//m_sound->SoundStop("GAMEBGM");
	//	}
	//}
	//else if (!m_sound->SoundPlaying("GAMEBGM")) {
	//	//m_sound->Sound2DPlay("GAMEBGM");
	//	m_sound->SoundStop("CHASE");
	//}
	if (!m_sound->SoundPlaying("GAMEBGM"))m_sound->Sound2DPlay("GAMEBGM");
}

void PlayScene::ScreenEffect()
{
	auto param = OptionParam::GetInstance();
	screen_efct->setLevelAfterMax(param->screen_bright);
}

bool PlayScene::seqSetTutorial(float delta_time) {
	m_alive_tutorial = true;
	m_factory->AddTutorialObject();
	TutorialCollision();
	m_skybox = dxe::Mesh::CreateCubeMV(30000, 20, 20);
	m_skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_c.png"));
	m_skybox->loadMaterial("material.bin");
	sequence_.change(&PlayScene::seqMainGame);
	return true;
}

bool PlayScene::seqSetMainGame(float delta_time) {
	m_alive_tutorial = false;
	m_skybox = nullptr;
	m_factory->AddMainObject();
	MainGameCollision();
	SetFogEnable(true);
	SetFogColor(0, 0, 0);
	SetLightDifColor(GetColorF(0.0f, 0.0f, 0.0f, 0));
	SetLightSpcColor(GetColorF(0.0f, 0.0f, 0.0f, 0));
	sequence_.change(&PlayScene::seqMainGame);
	return true;
}


bool PlayScene::seqMainGame(float delta_time) {
	m_factory->GetClassCamera()->GameCameraUpdate(m_factory->GetClassMediator());
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		m_subscene->setBoolInventory(true);
		sequence_.change(&PlayScene::seqOpenUI);
	}
	if (m_alive_tutorial) {
		for (auto obj_t : m_factory->GetClassObj_Tutorial()) {
			obj_t->Update(delta_time);
		}
	}
	for (auto obj : m_factory->GetClassObj()) {
		obj->Update(delta_time);
	}
	
	
	return true;
}

bool PlayScene::seqOpenUI(float delta_time) {
	if (!m_option->GetBoolOption()&& !m_subscene->getBoolInventory()) {
		sequence_.change(&PlayScene::seqMainGame);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		m_subscene->setBoolInventory(false);
		sequence_.change(&PlayScene::seqMainGame);
	}
	//マウスのゲットベロシティをオフにするべし！
	return true;
}

void PlayScene::CollitionFuc() {
	//プレイヤーと壁
	m_collision->registIntersectedProcess<Player, StageWall>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {

			std::shared_ptr<Player>pl = std::dynamic_pointer_cast<Player>(a);
			std::shared_ptr<StageWall>wall = std::dynamic_pointer_cast<StageWall>(b);
			pl->StageCorrection(wall);
		});
	//Enemyとプレイヤー
	m_collision->registIntersectedProcess<Player, Enemy>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {

			std::shared_ptr<Player>pl = std::dynamic_pointer_cast<Player>(a);
			std::shared_ptr<Enemy>enm = std::dynamic_pointer_cast<Enemy>(b);

			/*auto manager = GameManager::GetInstance();
			manager->can_clear = false;
			if(!manager->is_switch)manager->ChangeScene(std::make_shared<ResultScene>());
			manager->is_switch = true;*/
		});
	//Enemyと壁
	m_collision->registIntersectedProcess<Enemy, StageWall>(
		[](std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b) {

			
			std::shared_ptr<Enemy>enm = std::dynamic_pointer_cast<Enemy>(a);
			std::shared_ptr<StageWall>wall = std::dynamic_pointer_cast<StageWall>(b);

			enm->StageCorrection(wall);
		});

}
void PlayScene::MainGameCollision() {
	
	//ペアを代入
	
	m_enemy = m_factory->GetClassEnemy();
	m_collision->registPairObject<Player, Enemy>(m_player, m_enemy);

	m_stagewall = m_factory->GetClassStageWall();
	auto w = m_stagewall.begin();
	while (w != m_stagewall.end()) {
		m_collision->registPairObject<Player, StageWall>(m_player, *w);
		m_collision->registPairObject <Enemy, StageWall>(m_enemy, *w);
			w++; 
	}

}


void PlayScene::TutorialCollision() {
	
	m_stagewall = m_factory->GetClassStageTutorial();
	auto w = m_stagewall.begin();
	while (w != m_stagewall.end()) {
		m_collision->registPairObject<Player, StageWall>(m_player, *w);
		w++;
	}
}

