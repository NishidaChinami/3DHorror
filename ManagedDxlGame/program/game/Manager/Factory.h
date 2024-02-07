#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;
class GameObject;
class Player;
class GameCamera;
class Stage;
class StageWall;
class Enemy;
class Item;
class BackGroundStage;
class Sound;
class Fluorescent;
class Inventory;
class Message;

//-------------------------------------------------------------------------------------------------//
//Factoryクラス
// ゲームオブジェクトの生成クラス
//-------------------------------------------------------------------------------------------------//
class Factory
{
public:
	Factory();
	~Factory();
	//オブジェクトクラスをメディエータークラスに設定する
	void SetMediator();
	//メインゲームに使うオブジェクトの生成をする関数
	void CreatMainGame();
	//チュートリアルゲームに使うオブジェクトの生成をする関数
	void CreatTutorial();
	//CreatMainGameで生成したオブジェクトをObjectリストに入れる関数
	void AddMainObject();
	//CreatTutorialで生成したオブジェクトをTutorialObjectリスト関数
	void AddTutorialObject();

	//--------------------------Getter/Setter------------------------//
	//Factoryで生成したクラス
	std::list<std::shared_ptr<GameObject>> GetClassObj() { return object; }
	std::list<std::shared_ptr<GameObject>> GetClassObj_Tutorial() { return object_tutorial; }
	std::shared_ptr<GameCamera>GetClassCamera() { return gamecamera; }
	std::shared_ptr<Mediator>GetClassMediator() { return mediator; }
	std::shared_ptr<Player>GetClassPlayer() { return player; }
	std::shared_ptr<Stage>GetClassStage() { return stage; }
	std::shared_ptr<Enemy>GetClassEnemy() { return enemy; }
	std::list<std::shared_ptr<Item>>GetClassItemList(){ return item; }
	std::list<std::shared_ptr<Item>>GetClassTutorialItemList() { return item_tutorial; }
	std::list<std::shared_ptr<StageWall>>GetClassStageWall() { return stagewall; }
	std::list<std::shared_ptr<StageWall>>GetClassStageTutorial() { return tutorialstage; }
	std::shared_ptr<BackGroundStage>GetClassBackGroundStage() { return background; }
	std::shared_ptr<Inventory>GetClassInventory() { return inventory; }
	std::shared_ptr<Message>GetClassMessage() { return message; }
	
private:
	//チュートリアルマップのcsvハンドル
	std::vector<std::vector<int>> tutorial_csv;

	//------------生成するクラスのポインタ------------------------//
	//インターフェース的役割をもつメディエーターポインタ
	std::shared_ptr<Mediator>mediator = nullptr;
	//オブジェクトのリスト
	std::list<std::shared_ptr<GameObject>>object;
	//オブジェクトチュートリアルのリスト
	std::list<std::shared_ptr<GameObject>>object_tutorial;
	//カメラクラスのスマートポインタ
	std::shared_ptr<GameCamera>gamecamera = nullptr;
	//プレイヤーのスマートポインタ
	std::shared_ptr<Player>player = nullptr;
	//Enemyのスマートポインタ
	std::shared_ptr<Enemy>enemy = nullptr;
	//Itemのスマートポインタ
	std::list<std::shared_ptr<Item>>item;
	//チュートリアルでのみ使うItemのリスト
	std::list<std::shared_ptr<Item>>item_tutorial;
	//ステージ計算のクラス
	std::shared_ptr<Stage>stage = nullptr;
	//ステージの壁クラスリスト
	std::list<std::shared_ptr<StageWall>>stagewall;
	std::list<std::shared_ptr<StageWall>>tutorialstage;
	//ステージの描画クラス
	std::shared_ptr<BackGroundStage>background = nullptr;
	//照明クラスリスト
	std::list<std::shared_ptr<Fluorescent>>fluorescent;
	//文章のデータクラスポインタ
	std::shared_ptr<Message>message = nullptr;
	//インベントリー
	std::shared_ptr<Inventory>inventory = nullptr;


};
