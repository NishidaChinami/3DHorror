#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../GameObject.h"
#include"../../GameObject/Stage/Stage.h"
#include"../Stage/StageParts.h"

class GameCamera;
class Inventory;
class Mediator;

class Item: public GameObject, public std::enable_shared_from_this<Item>
{
public:
	enum class ItemType {
		Floppy,
		FrashLight,
		Battery,
		Pills,
		Medikit,
		Article
	};
	Item() {};
	Item(tnl::Vector3 pos,int articletype);
	Item(const tnl::Vector3 &pos,int type, const std::shared_ptr<Mediator>mediator);
	~Item();
	void Update(float delta_time)override;
	void PassInventory();
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	void ArticalEvent();

	tnl::Vector3 GetPos()const { return mesh->pos_; }
	tnl::Vector2i GetGridPos() const { return cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE); }

	ItemType GetType() const { return m_itemtype; }
	bool GetIsValid() { return m_isvalid; }
	std::string GetExplanation() { return m_item_explanation; }
	int GetUIHdl() { return m_item_hdl; }
	bool GetItem() { return m_getitem; }

	int GetfloopyCount() { return m_floppy_count; }

private:
	//何のアイテムか
	ItemType m_itemtype = ItemType::Floppy;
	//アイテムの描画のブール
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

	//プロッピーを集めた数
	int m_floppy_count = 0;

	//UIへの通知用フラグ
	//itemを持っているかどうか
	bool m_getitem = false;
	//記事をよんでいるかどうか
	bool m_readarticle = false;

	std::vector<std::vector<tnl::CsvCell>>item_detail_csv;

	std::shared_ptr<Mediator>m_mediator = nullptr;

};

