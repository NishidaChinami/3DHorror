#include "../dxlib_ext/dxlib_ext.h"
#include"Inventory.h"
#include"Slot.h"
#include"../../GameObject/Item/Item.h"

Inventory::Inventory()
{
	for (int i = 0; i < 4; ++i) {
		tnl::Vector3 s_pos = { 415 + i * 150.0f,DXE_WINDOW_HEIGHT/2,0 };
		m_slot.emplace_back(std::make_shared<Slot>(s_pos));
	}
}

Inventory::~Inventory()
{
}

void Inventory::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH/2,DXE_WINDOW_HEIGHT/2,0),INVENTORY_WIGHT,INVENTORY_HEIGHT,true,0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	for (auto slot : m_slot) {
		slot->Draw();
		slot->Explanation();
	}
	
}
bool Inventory::IsCanGetItem(const std::shared_ptr<Item>&item) {
	//itemî•ñ‚ð“n‚·
	auto getitem = m_slot.begin();
	while (getitem != m_slot.end()) {
		if ((*getitem)->m_is_valid == false) {
			(*getitem)->m_is_valid = true;
			(*getitem)->m_ui_hdl = item->GetUIHdl();
			(*getitem)->m_explanation = item->GetExplanation();
			(*getitem)->m_itemtype = item->GetType();
			return true;
		}
		else if ((*getitem)->m_itemtype == item->GetType()) {
			//”Žš‚ð‘‚â‚·
			(*getitem)->m_number++;
			return true;
		}

		getitem++;
	}
	return false;
}



void Inventory::UseInventory() {
	
}
