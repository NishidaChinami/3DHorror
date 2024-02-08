#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"Factory.h"
#include"Mediator.h"
//-------------------GameObject file------------------------//
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/GameObject.h"
#include"../GameObject/Stage/BackGroundStage.h"
#include"../GameObject/Stage/StageWall.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"
#include"../Effect/Light/Fluorescent.h"
//-------------------UI file------------------------//
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"


Factory::Factory()
{
	//オブジェクトの生成
	m_mediator = std::make_shared<Mediator>();
	m_gamecamera = std::make_shared<GameCamera>();
	m_player = std::make_shared<Player>(m_gamecamera,m_mediator);
	m_stage = std::make_shared<Stage>();
	m_inventory = std::make_shared<Inventory>();
	m_message = std::make_shared<Message>();
	m_background = std::make_shared<BackGroundStage>(m_stage,m_mediator);


	//チュートリアルで使うクラスのインスタンス生成
	CreatTutorial();
	//メインゲームで使うクラスのインスタンス生成
	CreatMainGame();
	//メディエターにオブジェクトを渡す
	SetMediator();

	//プレイヤーをオブジェクトリストに代入
	m_object_list.emplace_back(m_player);
	m_object_tutorial_list.emplace_back(m_player);
}

Factory::~Factory()
{

}
//------------------------------------------------------------------------------------------------------------
//メディエターにオブジェクトを渡す
void Factory::SetMediator() {
	m_mediator->SetPlayerClass(m_player);
	m_mediator->SetStageClass(m_stage);
	m_mediator->SetEnemyClass(m_enemy);
	m_mediator->SetItemClass(m_item_list);
	m_mediator->SetTutorialItemClass(m_item_tutorial_list);
	m_mediator->SetInventoryClass(m_inventory);
	m_mediator->SetMessageClass(m_message);
	m_mediator->SetBackGroundClass(m_background);
}
//------------------------------------------------------------------------------------------------------------
//メインゲームで使うクラスのインスタンス生成
void Factory::CreatMainGame() {
	//ステージクラス
	for (int r = 0; r < Stage::STAGE_ROW; r++) {
		for (int c = 0; c < Stage::STAGE_COL; c++) {
			tnl::Vector3 pos;
			pos.x = { -300.0f + c * StageWall::BLOCKSIZE };
			pos.y = StageWall::BLOCKHIGHT / 2;
			pos.z = { -300.0f + r * StageWall::BLOCKSIZE };
			//Emptyだったら壁を配置
			if (m_stage->getStgaeState(r, c) == maze::StageState::Wall)
			{
				m_stagewall_list.emplace_back(std::make_shared<StageWall>(pos, m_stage->getStgaeState(r, c),m_mediator));
			}
			//ゴールだったら、ゴールマスを配置
			else if (m_stage->getStgaeState(r, c) == maze::StageState::Goal) {
				m_stagewall_list.emplace_back(std::make_shared<StageWall>(pos, m_stage->getStgaeState(r, c),m_mediator));
			}
		}
	}
	//Enemy生成
	/*tnl::Vector2i a;
	if (stage->getStgaeState(1, 2) == maze::StageState::Empty) a = { 2,1 };
	else if (stage->getStgaeState(2, 1) == maze::StageState::Empty) a = { 1,2 };*/

	//enemy = std::make_shared<Enemy>(cf::Coordinate(a, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE, 100), mediator);
	
	//Enemy生成 プレイヤーがスポーンする位置と対角のエリアにライダムな場所にスポーン
	while (true)
	{
		tnl::Vector2i random;
		random.x = rand() % (Stage::STAGE_COL/ 2) + Stage::STAGE_COL / 2;
		random.y = rand() % (Stage::STAGE_ROW / 2) + Stage::STAGE_ROW / 2;
		if (m_stage->getStgaeState(random.y,random.x) == maze::StageState::Empty) {
			m_enemy = std::make_shared<Enemy>(cf::Coordinate(random, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE, 100), m_mediator);
			break;
		}
	}

	int count = 0;
	//Itemの生成
	while (count < 5)
	{
		tnl::Vector2i vec;
		//マップを6分割してエリア分けする
		switch (count)
		{
		case 0:vec = { Stage::STAGE_COL / 3,Stage::STAGE_ROW / 2 }; break;
			case 1:vec = { Stage::STAGE_COL * 2 / 3, Stage::STAGE_ROW / 2 }; break;
			case 2:vec = { 0,Stage::STAGE_ROW / 2 }; break;
			case 3:vec = { Stage::STAGE_COL / 3 ,0, }; break;
			case 4:vec = { Stage::STAGE_COL * 2 / 3,0 }; break;

			default:vec = { 0,0 }; break;
		}
		while (true)
		{
			tnl::Vector2i random;
			random.x = rand() % (Stage::STAGE_COL / 3);
			random.y = rand() % (Stage::STAGE_ROW / 2);
			if (m_stage->getStgaeState(random.y + vec.y, random.x + vec.x) == maze::StageState::Empty) {
				m_item_list.emplace_back(std::make_shared<Item>(cf::Coordinate(random + vec, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), Item::ItemType::Floppy, m_mediator));
				count++;
				break;
			}

		}

	}
	//ライトの生成
	for (int r = 1; r < Stage::STAGE_ROW; r+= 2) {
		for (int c = 1; c < Stage::STAGE_COL; c+=2) {
			tnl::Vector3 pos;
			pos.x = { -300.0f + c * StageWall::BLOCKSIZE };
			pos.y = 500;
			pos.z = { -300.0f + r * StageWall::BLOCKSIZE };
			//通路だったらライトを配置
			if(m_stage->getStgaeState(r, c) == maze::StageState::Empty)
				m_fluorescent_list.emplace_back(std::make_shared<Fluorescent>(pos,m_mediator));
		}
	}
	//懐中電灯を追加
	m_item_list.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(0, 0), StageWall::START_BLOCK_POS, 0), Item::ItemType::FrashLight, m_mediator));

}
//------------------------------------------------------------------------------------------------------------
//チュートリアルで使うクラスのインスタンス生成
void Factory::CreatTutorial() {
	m_tutorial_csv = tnl::LoadCsv<int>("csv/TutorialStage.csv");
	//チュートリアルマップの配置
	for (int i = 0; i < m_tutorial_csv.size(); i++) {
		for (int k = 0; k < m_tutorial_csv[i].size(); k++) {

			tnl::Vector3 pos;
			pos.x = { -300.0f + k * StageWall::BLOCKSIZE };
			pos.y = StageWall::BLOCKSIZE / 2;
			pos.z = { -300.0f + i * StageWall::BLOCKSIZE };
			if (m_tutorial_csv[i][k] != 0) {
				m_stage_tutorial_list.emplace_back(std::make_shared<StageWall>(pos));
			}
		}
	}
	//懐中電灯
	m_item_tutorial_list.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(6,6), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),Item::ItemType::FrashLight, m_mediator));
	//あらすじの説明アイテムの生成
	m_item_tutorial_list.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(4, 1), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE,400), 0, m_mediator));

}
//------------------------------------------------------------------------------------------------------------
//メインゲームに使うオブジェクトクラスをオブジェクトリストに入れる
void Factory::AddMainObject() {
	//壁クラス
	auto mazes = m_stagewall_list.begin();
	while (mazes != m_stagewall_list.end()) {
		m_object_list.emplace_back(*mazes);
		mazes++;
	}
	//照明クラス
	auto light = m_fluorescent_list.begin();
	while (light != m_fluorescent_list.end()) {
		m_object_list.emplace_back(*light);
		light++;
	}
	
	//敵クラス
	m_object_list.emplace_back(m_enemy);
	//アイテムクラス
	auto items = m_item_list.begin();
	while (items != m_item_list.end())
	{
		m_object_list.emplace_back(*items);
		items++;
	}
}
//------------------------------------------------------------------------------------------------------------
//チュートリアルゲームに使うオブジェクトクラスをオブジェクトリストに入れる
void Factory::AddTutorialObject() {
	//チュートリアルステージのクラス
	auto mazes = m_stage_tutorial_list.begin();
	while (mazes != m_stage_tutorial_list.end()) {
		m_object_tutorial_list.emplace_back(*mazes);
		mazes++;
	}
	//アイテムクラス
	auto items = m_item_tutorial_list.begin();
	while (items != m_item_tutorial_list.end())
	{
		m_object_tutorial_list.emplace_back(*items);
		items++;
	}
}