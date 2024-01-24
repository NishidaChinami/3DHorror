#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Factory.h"
#include"Mediator.h"
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/GameObject.h"
#include"../GameObject/Stage/BackGroudStage.h"
#include"../Effect/Sound/Sound.h"
#include"../Effect/Light/Fluorescent.h"
#include"../GameObject/Stage/StageParts.h"
#include"../UI/Inventory/Inventory.h"
#include"../UI/Message.h"

Factory::Factory()
{

	sound = std::make_shared<Sound>();
	mediator = std::make_shared<Mediator>();
	gamecamera = std::make_shared<GameCamera>();
	player = std::make_shared<Player>(sound,gamecamera);
	stage = std::make_shared<Stage>();
	inventory = std::make_shared<Inventory>();
	message = std::make_shared<Message>();
	
	CreatMesh();
	CreatTutorial();
	CreatMainGame();
	
	
	SetMediator();

	//オブジェクトリストに代入
	object.emplace_back(player);
	

	
}

Factory::~Factory()
{
}

void Factory::SetMediator() {
	mediator->SetPlayerClass(player);
	mediator->SetStageClass(stage);
	mediator->SetStageWallClass(stagewall);
	mediator->SetEnemyClass(enemy);
	mediator->SetItemClass(item);
	mediator->SetInventoryClass(inventory);
	mediator->SetMessageClass(message);
}

void Factory::CreatMesh() {
	//メッシュの用意
	groudmesh = dxe::Mesh::CreatePlaneMV(tnl::Vector3(BackGroudStage::SIZE, BackGroudStage::SIZE, 0));

	wallmesh = dxe::Mesh::CreateBoxMV
	(tnl::Vector3(StageWall::BLOCKSIZE, StageWall::BLOCKHIGHT, StageWall::BLOCKSIZE),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"),
		dxe::Texture::CreateFromFile("graphics/WallSample.jpg"));
	gaolmesh = dxe::Mesh::CreateBoxMV
	(tnl::Vector3(StageWall::BLOCKSIZE, StageWall::BLOCKHIGHT, StageWall::BLOCKSIZE),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"),
		dxe::Texture::CreateFromFile("graphics/Goal1.jpg"));

	soilmesh = dxe::Mesh::CreatePlaneMV(tnl::Vector3(StageWall::BLOCKSIZE, StageWall::BLOCKSIZE, 0));

	tutorialmesh = dxe::Mesh::CreateBoxMV
	(tnl::Vector3(StageWall::BLOCKSIZE, 1600, StageWall::BLOCKSIZE),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"),
		dxe::Texture::CreateFromFile("graphics/kabe1.jpg"));
}



void Factory::CreatMainGame() {
	mesh_index = 0;
	//チュートリアルステージの中身を一度クリア
	copy_mesh.clear();

	for (int row = -1; row < 4; row++) {
		for (int col = -1; col < 4; col++) {
			copy_groud_mesh.emplace_back(groudmesh->createClone());
			copy_groud_mesh.emplace_back(groudmesh->createClone());
			tnl::Vector3 groudpos;
			groudpos.x = BackGroudStage::SIZE * col;
			groudpos.y = 0;
			groudpos.z = BackGroudStage::SIZE * row;
			backgroud.emplace_back(std::make_shared<BackGroudStage>(groudpos, copy_groud_mesh[mesh_index], copy_groud_mesh[mesh_index + 1]));
			mesh_index += 2;
		}
	}
	mesh_index = 0;

	for (int r = 0; r < stage->m_row; r++) {
		for (int c = 0; c < stage->m_col; c++) {
			tnl::Vector3 pos;
			pos.x = { -300.0f + c * StageWall::BLOCKSIZE };
			pos.z = { -300.0f + r * StageWall::BLOCKSIZE };
			if (stage->GetStgaeState(r, c) == maze::StageState::Wall)
			{
				//クローンを作るためにメッシュのコピー
				copy_mesh.emplace_back(wallmesh->createClone());
				stagewall.emplace_back(std::make_shared<StageWall>(pos, stage->GetStgaeState(r, c), copy_mesh[mesh_index],mediator));
				mesh_index++;
			}
			else if (stage->GetStgaeState(r, c) == maze::StageState::Goal) {
				stagewall.emplace_back(std::make_shared<StageWall>(pos, stage->GetStgaeState(r, c), gaolmesh,mediator));
			}
		}
	}
	//Enemy生成
	enemy = std::make_shared<Enemy>(cf::Coordinate(tnl::Vector2i(1, 1), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE, 50), mediator, sound);

	/*while (true)
	{
		tnl::Vector2i random;
		random.x = rand() % (stage->m_col/ 2) + stage->m_col / 2;
		random.y = rand() % (stage->m_row / 2) + stage->m_row / 2;
		if (stage->GetStgaeState(random.y,random.x) == maze::StageState::Empty) {
			enemy = std::make_shared<Enemy>(cf::Coordinate(random, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE, 50), mediator, sound);
			break;
		}
	}*/

	int count = 0;
	//Itemの生成
	while (count < 5)
	{
		tnl::Vector2i vec;

		switch (count)
		{
		case 0:vec = { stage->m_col / 3,stage->m_row / 2 }; break;
		case 1:vec = { stage->m_col * 2 / 3, stage->m_row / 2 }; break;
		case 2:vec = { 0,stage->m_row / 2 }; break;
		case 3:vec = { stage->m_col / 3 ,0, }; break;
		case 4:vec = { stage->m_col * 2 / 3,0 }; break;

		default:vec = { 0,0 }; break;
		}
		while (true)
		{
			tnl::Vector2i random;
			random.x = rand() % (stage->m_col / 3);
			random.y = rand() % (stage->m_row / 2);
			if (stage->GetStgaeState(random.y + vec.y, random.x + vec.x) == maze::StageState::Empty) {
				item.emplace_back(std::make_shared<Item>(cf::Coordinate(random + vec, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), 0, mediator));
				count++;
				break;
			}

		}

	}
	//ライト
	for (int r = 1; r < stage->m_row; r+= 2) {
		for (int c = 1; c < stage->m_col; c+=2) {
			tnl::Vector3 pos;
			pos.x = { -300.0f + c * StageWall::BLOCKSIZE };
			pos.y = 400;
			pos.z = { -300.0f + r * StageWall::BLOCKSIZE };
			fluorescent.emplace_back(std::make_shared<Fluorescent>(pos));
		}
	}
	

}

void Factory::CreatTutorial() {
	tutorial_csv = tnl::LoadCsv<int>("csv/TutorialStage.csv");

	for (int i = 0; i < tutorial_csv.size(); i++) {
		for (int k = 0; k < tutorial_csv[i].size(); k++) {

			tnl::Vector3 pos;
			pos.x = { -300.0f + k * StageWall::BLOCKSIZE };
			pos.y = StageWall::BLOCKSIZE / 2;
			pos.z = { -300.0f + i * StageWall::BLOCKSIZE };
			if (tutorial_csv[i][k] == 1) {
				copy_mesh.emplace_back(tutorialmesh->createClone());
				tutorialstage.emplace_back(std::make_shared<StageWall>(pos, copy_mesh[mesh_index]));
			}
			else if (tutorial_csv[i][k] == 0) {
				copy_mesh.emplace_back(soilmesh->createClone());
				soilgroud.emplace_back(std::make_shared<BackGroudStage>(pos, copy_mesh[mesh_index]));
			}
			mesh_index++;
		}
	}
	item_tutorial.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(3,6), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE), 1, mediator));
	//予兆ストーリーの代入
	item_tutorial.emplace_back(std::make_shared<Item>(cf::Coordinate(tnl::Vector2i(5, 1), StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE),1));
}


void Factory::AddMainObject() {
	auto mazes = stagewall.begin();
	while (mazes != stagewall.end()) {
		object.emplace_back(*mazes);
		mazes++;
	}
	auto light = fluorescent.begin();
	while (light != fluorescent.end()) {
		object.emplace_back(*light);
		light++;
	}
	object.emplace_back(enemy);

	auto items = item.begin();
	while (items != item.end())
	{
		object.emplace_back(*items);
		items++;
	}
}


void Factory::AddTutorialObject() {
	auto mazes = tutorialstage.begin();
	while (mazes != tutorialstage.end()) {
		object_tutorial.emplace_back(*mazes);
		mazes++;
	}
	auto items = item_tutorial.begin();
	while (items != item_tutorial.end())
	{
		object.emplace_back(*items);
		object_tutorial.emplace_back(*items);
		//item.emplace_back(item);
		items++;
	}
}