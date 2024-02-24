#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../GameObject.h"
#include"../../GameObject/Stage/Stage.h"
#include"../Stage/StageWall.h"

class GameCamera;
class Inventory;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//アイテムクラス
// 脱出のために必要なアイテムやシナリオを持つアイテムを実装
// 取ったアイテムはインベントリーに伝えられる
//-------------------------------------------------------------------------------------------------//

class Item: public GameObject, public std::enable_shared_from_this<Item>
{
public:
	//Itemの種類のEnumクラス
	enum class ItemType {
		Floppy,
		FrashLight,
		Battery,
		Pills,
		Medikit,
		Article
	};
	Item() {};

	//ストーリーをもつアイテムのコンストラクタ
	//第1引数　生成座標
	//第2引数　ストーリーの番号
	//第3引数　オブジェクトの参照クラスメディエーターのポインタ
	Item(tnl::Vector3 pos, int articletype, const std::shared_ptr<Mediator>&mediator);
	//MV1Modelを持つアイテムのコンストラクタ
	//第1引数　生成座標
	//第2引数　アイテムの種類
	//第3引数　オブジェクトの参照クラスメディエーターのポインタ
	Item(const tnl::Vector3 &pos, ItemType type, const std::shared_ptr<Mediator>&mediator);
	~Item();
	//更新処理
	void Update(float delta_time)override;
	//描画処理
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//インベントリーにしまえるかの判定とアイテムの情報を伝える
	void PassInventory();

	//--------------------------Getter/Setter------------------------//
	const tnl::Vector3 &getPos()const { return mesh->pos_; }
	const tnl::Vector2i &getGridPos() const { return cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE); }
	const ItemType &getType() const { return m_itemtype; }
	bool getIsValid()const { return m_isvalid; }
	const std::string &getExplanation() const{ return m_item_explanation; }
	int getUIHdl() const{ return m_item_hdl; }
	bool getItem() const{ return m_getitem; }

	TNL_PROPERTY(bool, ReadArticle, m_readarticle);
private:
	//何のアイテムか
	ItemType m_itemtype = ItemType::Floppy;
	//アイテムの描画のフラグ
	bool m_isvalid = true;
	//アイテムの説明文
	std::string m_item_explanation;
	//UI用の画像
	int m_item_hdl = 0;
	//アイテムのmodelハンドル
	int m_item_model_hdl;
	//アイテムのテクスチャーハンドル
	int m_item_texture_hdl;
	//modelのスケール
	float m_scale;
	//記事の種類
	int m_article_type;
	//アイテムの取得可能距離
	const float ITEM_RANGE = 800;
	//UIへの通知用フラグ
	//itemを持っているかどうか
	bool m_getitem = false;
	//記事をよんでいるかどうか
	bool m_readarticle = false;

	//アイテムのUI画像やmodelのMV1ファイル、テクスチャーなどの情報を管理するcsvファイルのロード用ベクター
	std::vector<std::vector<tnl::CsvCell>>item_detail_csv;

	//------------他クラスの参照用ポインタ------------------------//
	//ほかのオブジェクトクラスの参照用ポインタ
	std::shared_ptr<Mediator>m_mediator = nullptr;

	//----------------------定数------------------------//
	const tnl::Vector3 ITEM_MESS_POS = { 0,100,0 };

};

