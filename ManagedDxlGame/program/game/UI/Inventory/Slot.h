#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/Item/Item.h"

class Slot
{
public:
	Slot(const tnl::Vector3 &pos);
	~Slot();
	//描画
	void Draw();

	//説明文の表示
	void Explanation();

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
private:
	tnl::Vector3 m_pos;

	const float SLOTSIZE = 100;
};

