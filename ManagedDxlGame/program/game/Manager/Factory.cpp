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
#include"../GameObject/Stage/BackGroudStage.h"
#include"../GameObject/Stage/StageParts.h"
//-------------------Effect file------------------------//
#include"../Effect/Sound/Sound.h"
#include"../Effect/Light/Fluorescent.h"
//-------------------UI file------------------------//
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"


Factory::Factory()
{
	//オブジェクトの生成
	mediator = std::make_shared<Mediator>();
	gamecamera = std::make_shared<GameCamera>();
	player = std::make_shared<Player>(gamecamera,mediator);
	stage = std::make_shared<Stage>();
	inventory = std::make_shared<Inventory>();
	message = std::make_shared<Message>();
	backgroud = std::make_shared<BackGroudStage>(stage,mediator);


	//チュートリアルで使うクラスのインスタンス生成
	CreatTutorial();
	//メインゲームで使うクラスのインスタンス生成
	CreatMainGame();
	//メディエターにオブジェクトを渡す
	SetMediator();

	//プレイヤーをオブジェクトリストに代入
	object.emplace_back(player);
	object_tutorial.emplace_back(player);
}

Factory::~Factory()
{
}
//------------------------------------------------------------------------------------------------------------
//メディエターにオブジェクトを渡す
void Factory::SetMediator() {
	mediator->SetPlayerClass(player);
	mediator->SetStageClass(stage);
	mediator->SetStageWallClass(stagewall);
	mediator->SetEnemyClass(enemy);
	mediator->SetItemClass(item);
	mediator->SetTutorialItemClass(item_tutorial);
	mediator->SetInventoryClass(inventory);
	mediator->SetMessageClass(message);
	mediator->SetBackGroundClass(backgroud);
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
			if (stage->getStgaeState(r, c) == maze::StageState::Wall)
			{
				stagewall.emplace_back(std::make_shared<StageWall>(pos, stage->getStgaeState(r, c),mediator));
			}
			//ゴールだったら、ゴールマスを配置
			else if (stage->getStgaeState(r, c) == maze::StageState::Goal) {
				stagewall.emplace_back(std::make_shared<StageWall>(pos, stage->getStgaeState(r, c),mediator));
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
		if (stage->getStgaeState(random.y,random.x) == maze::StageState::Empty) {
			enemy = std::make_shared<Enemy>(cf::Coordinate(random, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE, 100), mediator);
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
			if (stage->getStgaeState(random.y + vec.y, random.x + vec.x) == maze::StageState::Empty) {
				item.emplace_back(std::make_shared<Item>(cf::Coordinate(random + vec, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), Item::ItemType::Floppy, mediator));
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
			if(stage->getStgaeState(r, c) == maze::StageState::Empty)
				fluorescent.emplace_back(std::make_shared<Fluorescent>(pos,mediator));
		}
	}
	//懐中電灯を追加
	item.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(0, 0), StageWall::START_BLOCK_POS, 0), Item::ItemType::FrashLight, mediator));

}
//------------------------------------------------------------------------------------------------------------
//チュートリアルで使うクラスのインスタンス生成
void Factory::CreatTutorial() {
	tutorial_csv = tnl::LoadCsv<int>("csv/TutorialStage.csv");
	//チュートリアルマップの配置
	for (int i = 0; i < tutorial_csv.size(); i++) {
		for (int k = 0; k < tutorial_csv[i].size(); k++) {

			tnl::Vector3 pos;
			pos.x = { -300.0f + k * StageWall::BLOCKSIZE };
			pos.y = StageWall::BLOCKSIZE / 2;
			pos.z = { -300.0f + i * StageWall::BLOCKSIZE };
			if (tutorial_csv[i][k] != 0) {
				tutorialstage.emplace_back(std::make_shared<StageWall>(pos));
			}
		}
	}
	//懐中電灯
	item_tutorial.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(6,6), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),Item::ItemType::FrashLight, mediator));
	//あらすじの説明アイテムの生成
	item_tutorial.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(4, 1), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE,400), 0, mediator));

}
//------------------------------------------------------------------------------------------------------------
//メインゲームに使うオブジェクトクラスをオブジェクトリストに入れる
void Factory::AddMainObject() {
	//壁クラス
	auto mazes = stagewall.begin();
	while (mazes != stagewall.end()) {
		object.emplace_back(*mazes);
		mazes++;
	}
	//照明クラス
	auto light = fluorescent.begin();
	while (light != fluorescent.end()) {
		object.emplace_back(*light);
		light++;
	}
	//敵クラス
	object.emplace_back(enemy);
	//アイテムクラス
	auto items = item.begin();
	while (items != item.end())
	{
		object.emplace_back(*items);
		items++;
	}
}
//------------------------------------------------------------------------------------------------------------
//チュートリアルゲームに使うオブジェクトクラスをオブジェクトリストに入れる
void Factory::AddTutorialObject() {
	//チュートリアルステージのクラス
	auto mazes = tutorialstage.begin();
	while (mazes != tutorialstage.end()) {
		object_tutorial.emplace_back(*mazes);
		mazes++;
	}
	//アイテムクラス
	auto items = item_tutorial.begin();
	while (items != item_tutorial.end())
	{
		object_tutorial.emplace_back(*items);
		items++;
	}
}