#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"


class Player;
class StageWall;
class GameCamera;
class Stage;
class Enemy;
class Item;
class Inventory;
class Message;
class BackGroudStage;

//-------------------------------------------------------------------------------------------------//
//メディエータークラス
// オブジェクトの参照先を一つに集約する役割
//-------------------------------------------------------------------------------------------------//
class Mediator
{
public:
	Mediator() {};
	~Mediator() {};

	//--------------------playerのGetterとSetter------------------------------------------------//
	
	//プレイヤーの座標
	tnl::Vector3 MGetPlayerPos();
	//プレイヤーの回転
	tnl::Quaternion MGetPlayerRot();
	//プレイヤーのサイズ
	tnl::Vector3 MGetPlayerSize();
	//プレイヤーのスピード
	float MGetPlayerSpeed();
	//プレイヤーのスタミナ
	float MGetPlayerStamina();
	//走れるかどうかのフラグ
	bool MGetPlayerDash();

	//--------------------EnemyのGetterとSetter------------------------------------------------//

	//Enemyの座標
	tnl::Vector3 MGetEnemyPos();
	//Enemyのサイズ
	tnl::Vector3 MGetEnemySize();
	//プレイヤーを見つけているかどうかのフラフ
	bool MGetChaseState();

	//--------------------ステージのGetterとSetter------------------------------------------------//
	//stageのstagestate２次元配列の取得
	//第1引数 列数
	//第2引数 行数
	//ret そのマスの迷路ステートを返す
	maze::StageState MGetStageState(int r, int c);

	//-------------------アイテムのGetterとSetter------------------------------------------------//
	
	//Itemの位置を取得
	std::vector<tnl::Vector2i> MGetItemPos();
	//フロッピーディスクが5枚集まったかどうかのフラグ
	bool MGetItemFloopy();
	//記事を読んでいるかのフラグ
	bool MGetReadArticle ();
	void MSetReadArticle(bool read);

	//-------------------メッセージのGetterとSetter------------------------------------------------//
	//表示するメッセージの情報を登録する
	void MSetMessage(int title);
	//何のストーリーか取得する
	int MGetTitleType();

	//-------------------インベントリーのGetterとSetter------------------------------------------------//
	//アイテムの情報をインベントリーの渡す
	bool MSetPassInventory(const std::shared_ptr<Item>& item);

	//skyboxのパラメーターの設定
	void MSetSkyEmissive(tnl::Vector3 param);
	tnl::Vector3 MGetSkyEmissive();

	//-------------------メディエータークラスに必要なクラスのポインタ------------------------------------------------//
	void SetPlayerClass(const std::shared_ptr<Player>&player) { m_player = player; }
	void SetStageClass(const std::shared_ptr<Stage>&stage) { m_stage = stage; }
	void SetStageWallClass(const std::list<std::shared_ptr<StageWall>>& stagewall) { m_stagewall_list= stagewall; }
	void SetEnemyClass(std::shared_ptr<Enemy>&enemy) { m_enemy = enemy; }
	void SetItemClass(const std::list<std::shared_ptr<Item>>& item) { m_item_list = item; }
	void SetTutorialItemClass(const std::list<std::shared_ptr<Item>>& tutorial_item) { m_tutorialitem_list = tutorial_item; }
	void SetMessageClass(const std::shared_ptr<Message>& message) { m_message = message; }
	void SetInventoryClass(const std::shared_ptr<Inventory>& inventory) { m_inventory = inventory; }
	void SetBackGroundClass(const std::shared_ptr<BackGroudStage>& background) { m_backgroundstage = background; }

	void MSetLightParam(bool light) { m_getlight = light; }
	bool MGetLightParam() { return m_getlight; }
private:
	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Player>m_player = nullptr;
	std::list<std::shared_ptr<StageWall>>m_stagewall_list;
	std::shared_ptr<GameCamera>m_camera = nullptr;
	std::shared_ptr<Stage>m_stage = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<Item>>m_item_list;
	std::list<std::shared_ptr<Item>>m_tutorialitem_list;
	std::shared_ptr<Message>m_message = nullptr;
	std::shared_ptr<Inventory>m_inventory = nullptr;
	std::shared_ptr<BackGroudStage>m_backgroundstage = nullptr;

	//ライトをゲットしたかどうか
	bool m_getlight = false;


};
