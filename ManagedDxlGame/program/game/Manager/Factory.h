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
	const std::list<std::shared_ptr<GameObject>> &GetClassObj() { return m_object_list; }
	const std::list<std::shared_ptr<GameObject>> &GetClassObj_Tutorial() { return m_object_tutorial_list; }
	const std::shared_ptr<GameCamera>&GetClassCamera() { return m_gamecamera; }
	const std::shared_ptr<Mediator>&GetClassMediator() { return m_mediator; }
	const std::shared_ptr<Player>&GetClassPlayer() { return m_player; }
	const std::shared_ptr<Stage>&GetClassStage() { return m_stage; }
	const std::shared_ptr<Enemy>&GetClassEnemy() { return m_enemy; }
	const std::list<std::shared_ptr<Item>>&GetClassItemList(){ return m_item_list; }
	const std::list<std::shared_ptr<Item>>&GetClassTutorialItemList() { return m_item_tutorial_list; }
	const std::list<std::shared_ptr<StageWall>>&GetClassStageWall() { return m_stagewall_list; }
	const std::list<std::shared_ptr<StageWall>>&GetClassStageTutorial() { return m_stage_tutorial_list; }
	const std::shared_ptr<BackGroundStage>&GetClassBackGroundStage() { return m_background; }
	const std::shared_ptr<Inventory>&GetClassInventory() { return m_inventory; }
	const std::shared_ptr<Message>&GetClassMessage() { return m_message; }
	
private:
	//チュートリアルマップのcsvハンドル
	std::vector<std::vector<int>> m_tutorial_csv;

	//------------生成するクラスのポインタ------------------------//
	//インターフェース的役割をもつメディエーターポインタ
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//オブジェクトのリスト
	std::list<std::shared_ptr<GameObject>>m_object_list;
	//オブジェクトチュートリアルのリスト
	std::list<std::shared_ptr<GameObject>>m_object_tutorial_list;
	//カメラクラスのスマートポインタ
	std::shared_ptr<GameCamera>m_gamecamera = nullptr;
	//プレイヤーのスマートポインタ
	std::shared_ptr<Player>m_player = nullptr;
	//Enemyのスマートポインタ
	std::shared_ptr<Enemy>m_enemy = nullptr;
	//Itemのスマートポインタ
	std::list<std::shared_ptr<Item>>m_item_list;
	//チュートリアルでのみ使うItemのリスト
	std::list<std::shared_ptr<Item>>m_item_tutorial_list;
	//ステージ計算のクラス
	std::shared_ptr<Stage>m_stage = nullptr;
	//ステージの壁クラスリスト
	std::list<std::shared_ptr<StageWall>>m_stagewall_list;
	std::list<std::shared_ptr<StageWall>>m_stage_tutorial_list;
	//ステージの描画クラス
	std::shared_ptr<BackGroundStage>m_background = nullptr;
	//照明クラスリスト
	std::list<std::shared_ptr<Fluorescent>>m_fluorescent_list;
	//文章のデータクラスポインタ
	std::shared_ptr<Message>m_message = nullptr;
	//インベントリー
	std::shared_ptr<Inventory>m_inventory = nullptr;


};
