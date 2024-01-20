#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/// <summary>
/// Objectクラスのインスタンス生成クラス
/// </summary>

class Mediator;
class GameObject;
class Player;
class GameCamera;
class Stage;
class StageWall;
class Enemy;
class Item;
class BackGroudStage;
class Sound;
class Fluorescent;
class Inventory;
class Message;

class Factory
{
public:
	Factory();
	~Factory();
	void SetMediator();
	//void Update() {};
	void CreatMesh();
	void CreatMainGame();
	void CreatTutorial();

	void AddMainObject();
	void AddTutorialObject();


	std::list<std::shared_ptr<GameObject>> GetClassObj() { return object; }
	std::list<std::shared_ptr<GameObject>> GetClassObj_Tutorial() { return object_tutorial; }


	std::shared_ptr<GameCamera>GetClassCamera() { return gamecamera; }
	std::shared_ptr<Mediator>GetClassMediator() { return mediator; }
	std::shared_ptr<Player>GetClassPlayer() { return player; }
	std::shared_ptr<Stage>GetClassStage() { return stage; }
	std::shared_ptr<Enemy>GetClassEnemy() { return enemy; }
	std::list<std::shared_ptr<Item>>GetClassItemList(){ return item; }

	std::list<std::shared_ptr<StageWall>>GetClassStageWall() { return stagewall; }
	std::list<std::shared_ptr<StageWall>>GetClassStageTutorial() { return tutorialstage; }
	std::list<std::shared_ptr<BackGroudStage>>GetClassBackGroudStage() { return backgroud; }
	std::list<std::shared_ptr<BackGroudStage>>GetClassSoilGroudStage() { return soilgroud; }

	std::shared_ptr<Sound>GetClassSound() { return sound; }
	//std::list<std::shared_ptr<Fluorescent>>GetClassLightList() { return fluorescent; }
	std::shared_ptr<Inventory>GetClassInventory() { return inventory; }
	std::shared_ptr<Message>GetClassMessage() { return message; }
	
private:
	//インターフェース的役割をもつメディエーターポインタ
	std::shared_ptr<Mediator>mediator = nullptr;
	//オブジェクトのリストポインタ
	std::list<std::shared_ptr<GameObject>>object;
	std::list<std::shared_ptr<GameObject>>object_tutorial;

	//カメラクラスのスマートポインタ
	std::shared_ptr<GameCamera>gamecamera = nullptr;
	//プレイヤーのスマートポインタ
	std::shared_ptr<Player>player = nullptr;
	//Enemyのスマートポインタ
	std::shared_ptr<Enemy>enemy = nullptr;
	//Itemのスマートポインタ
	std::list<std::shared_ptr<Item>>item;
	std::list<std::shared_ptr<Item>>item_tutorial;

	//サウンドクラス
	std::shared_ptr<Sound>sound;
	//ステージ計算のクラス
	std::shared_ptr<Stage>stage = nullptr;
	//ステージの壁クラスリスト
	std::list<std::shared_ptr<StageWall>>stagewall;
	std::list<std::shared_ptr<StageWall>>tutorialstage;
	//ステージの天井と床のリスト
	std::list<std::shared_ptr<BackGroudStage>>backgroud;
	std::list<std::shared_ptr<BackGroudStage>>soilgroud;
	
	//照明クラスリスト
	std::list<std::shared_ptr<Fluorescent>>fluorescent;
	//文章のデータクラスポインタ
	std::shared_ptr<Message>message = nullptr;
	//インベントリー
	std::shared_ptr<Inventory>inventory = nullptr;
	

	//コピーメッシュ
	std::shared_ptr<dxe::Mesh>groudmesh = nullptr;
	std::vector<std::shared_ptr<dxe::Mesh>>copy_groud_mesh;

	std::shared_ptr<dxe::Mesh>wallmesh = nullptr;
	std::vector<std::shared_ptr<dxe::Mesh>>copy_mesh;

	std::shared_ptr<dxe::Mesh>gaolmesh = nullptr;

	std::shared_ptr<dxe::Mesh>soilmesh = nullptr;
	std::shared_ptr<dxe::Mesh>tutorialmesh = nullptr;
	

	//メッシュのインデックス
	int mesh_index = 0;

	//チュートリアルマップのcsvハンドル
	std::vector<std::vector<int>> tutorial_csv;

};
