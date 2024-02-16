#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Slot;
class Item;
//-------------------------------------------------------------------------------------------------//
//プレイヤーのインベントリー
//-------------------------------------------------------------------------------------------------//
class Inventory
{
public:
	Inventory();
	~Inventory(){}
	//アイテムの情報をもらってインベントリーに反映させる処理
	bool IsCanGetItem(const std::shared_ptr<Item>&item);
	//インベントリーの描画
	void Draw();
private:
	//スロットのポインタ
	std::vector<std::shared_ptr<Slot>>m_slot_vector;

	//------------------------------定数------------------------------------------//
	//インベントリーの外枠のサイズ
	const float INVENTORY_WIGHT = 600;
	const float INVENTORY_HEIGHT = 220;
	tnl::Vector3 INVENTORY_POS = { 370,280,0 };
	tnl::Vector3 SLOT_POS = { 415,360,0 };
};

