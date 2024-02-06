#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/Item/Item.h"

//-------------------------------------------------------------------------------------------------//
//プレイヤーのインベントリー
//-------------------------------------------------------------------------------------------------//
class Slot
{
public:
	Slot(const tnl::Vector3 &pos):m_pos(pos){}
	~Slot();
	//描画処理
	void Draw();
	//説明文の表示の処理
	void Explanation();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	TNL_PROPERTY(int, SlotHandle, m_ui_hdl);
	TNL_PROPERTY(int, SlotNum, m_number);
	TNL_PROPERTY(std::string, SlotExlanation, m_explanation);
	TNL_PROPERTY(bool, SlotValid, m_is_valid);
	TNL_PROPERTY(Item::ItemType, SlotItemType, m_itemtype);

private:
	//スロットの中に移る画像ハンドル
	int m_ui_hdl = 0;
	//表示する個数
	int m_number = 1;
	//説明文
	std::string m_explanation;
	//物が入っているかどうか
	bool m_is_valid = false;
	//アイテムタイプ
	Item::ItemType m_itemtype;
	//取得したアイテムのUI画像の２D座標
	tnl::Vector3 m_pos;
	//スロットの枠のサイズ
	const float SLOTSIZE = 100;
};

