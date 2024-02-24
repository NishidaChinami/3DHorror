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
class BackGroundStage;

//-------------------------------------------------------------------------------------------------//
//メディエータークラス
// オブジェクトの参照先を一つに集約する役割
// メディエターパターンを実装したかったが、実際はデーターマネージャのような働きをしている
//-------------------------------------------------------------------------------------------------//
class Mediator
{
public:
	Mediator() {
		m_intersect_stage = new tnl::Vector3();
	}
	~Mediator() {
		delete m_intersect_stage;
	}

	//--------------------playerのGetterとSetter------------------------------------------------//
	
	//プレイヤーの座標
	const tnl::Vector3 &MGetPlayerPos()const;
	//プレイヤーの回転
	const tnl::Quaternion &MGetPlayerRot()const;
	//プレイヤーのサイズ
	const tnl::Vector3 &MGetPlayerSize()const;
	//プレイヤーのスピード
	float MGetPlayerSpeed()const;
	//プレイヤーのスタミナ
	float MGetPlayerStamina()const;
	//走れるかどうかのフラグ
	bool MGetPlayerDash()const;

	//--------------------EnemyのGetterとSetter------------------------------------------------//

	//Enemyの座標
	const tnl::Vector3 &MGetEnemyPos()const;
	//Enemyのサイズ
	const tnl::Vector3 &MGetEnemySize()const;
	//プレイヤーを見つけているかどうかのフラフ
	bool MGetChaseState()const;

	//--------------------ステージのGetterとSetter------------------------------------------------//
	//stageのstagestate２次元配列の取得
	//第1引数 列数
	//第2引数 行数
	//ret そのマスの迷路ステートを返す
	const maze::StageState &MGetStageState(int r, int c)const;
	//Rayがステージの壁にぶつかる交点と比較対象の交点のどちらが近いかを判定する
	//第1引数　Rayを出すものの座標
	//第2引数　Rayの向き
	//第3引数　比較対象の交点座標
	//ret 壁が近い場合true 比較対象が近い場合falseを返す
	bool MGetIntersectStage(const tnl::Vector3 &pos, const tnl::Vector3 &ray, tnl::Vector3 *intersect_point )const;

	//-------------------アイテムのGetterとSetter------------------------------------------------//
	
	//Itemの位置を取得
	const std::vector<tnl::Vector2i> &MGetItemPos();
	//フロッピーディスクが5枚集まったかどうかのフラグ
	bool MGetItemFloopy()const;
	//記事を読んでいるかのフラグ
	bool MGetReadArticle ()const;
	void MSetReadArticle(bool read);

	//-------------------メッセージのGetterとSetter------------------------------------------------//
	//表示するメッセージの情報を登録する
	void MSetMessage(int title);
	//何のストーリーか取得する
	int MGetTitleType()const;

	//-------------------インベントリーのGetterとSetter------------------------------------------------//
	//アイテムの情報をインベントリーの渡す
	bool MSetPassInventory(const std::shared_ptr<Item>& item);

	//skyboxのパラメーターの設定
	void MSetSkyEmissive(tnl::Vector3 &param);
	const tnl::Vector3 &MGetSkyEmissive()const;

	//-------------------メディエータークラスに必要なクラスのポインタ------------------------------------------------//
	void SetPlayerClass(std::shared_ptr<Player>&player) { m_player = player; }
	void SetStageClass(std::shared_ptr<Stage>&stage) { m_stage = stage; }
	void SetEnemyClass(std::shared_ptr<Enemy>&enemy) { m_enemy = enemy; }
	void SetItemClass(std::list<std::shared_ptr<Item>>& item) { for (auto list : item) { m_item_list.emplace_back(list); } }
	void SetTutorialItemClass(std::list<std::shared_ptr<Item>>& tutorial_item) { for (auto list : tutorial_item) { m_tutorialitem_list.emplace_back(list); } }
	void SetMessageClass(std::shared_ptr<Message>& message) { m_message = message; }
	void SetInventoryClass(std::shared_ptr<Inventory>& inventory) { m_inventory = inventory; }
	void SetBackGroundClass(std::shared_ptr<BackGroundStage>& background) { m_backgroundstage = background; }
	void SetStageWallClass(std::list<std::shared_ptr<StageWall>>& stagewall) { for (auto list : stagewall) { m_stagewall_list.emplace_back(list); } }


	void MSetLightParam(bool light) { m_getlight = light; }
	bool MGetLightParam()const { return m_getlight; }
private:
	//------------他クラスの参照用ポインタ------------------------//
	//相互参照を防ぐためにweak_ptrを使用
	std::weak_ptr<Player>m_player;
	std::weak_ptr<GameCamera>m_camera;
	std::weak_ptr<Stage>m_stage;
	std::weak_ptr<Enemy>m_enemy;
	std::list<std::weak_ptr<Item>>m_item_list;
	std::list<std::weak_ptr<Item>>m_tutorialitem_list;
	std::weak_ptr<Message>m_message;
	std::weak_ptr<Inventory>m_inventory;
	std::weak_ptr<BackGroundStage>m_backgroundstage;
	std::list<std::weak_ptr<StageWall>>m_stagewall_list;
	//ライトをゲットしたかどうか
	bool m_getlight = false;

	//交点のポインタ
	tnl::Vector3* m_intersect_stage = nullptr;
};
