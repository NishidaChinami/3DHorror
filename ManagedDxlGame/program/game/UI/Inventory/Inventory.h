#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Slot;
class Item;
class Inventory
{
public:
	Inventory();
	~Inventory();

	//void PassItemInfo(std::shared_ptr<Item>item);
	void UseInventory();

	bool IsCanGetItem(const std::shared_ptr<Item>&item);
	void Draw();
private:
	std::vector<std::shared_ptr<Slot>>m_slot;

	const float INVENTORY_WIGHT = 600;
	const float INVENTORY_HEIGHT = 200;
};

