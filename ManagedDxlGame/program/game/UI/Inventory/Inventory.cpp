#include "../dxlib_ext/dxlib_ext.h"
#include"Inventory.h"
#include"Slot.h"
#include"../../GameObject/Item/Item.h"

Inventory::Inventory()
{
	//�C���x���g���[�̃X���b�g�̐���
	for (int i = 0; i < 4; ++i) {
		tnl::Vector3 s_pos = { 415 + i * 150.0f,DXE_WINDOW_HEIGHT/2,0 };
		m_slot.emplace_back(std::make_shared<Slot>(s_pos));
	}
}

//------------------------------------------------------------------------------------------------------------
//�C���x���g���[�̕`��
void Inventory::Draw() {
	//�C���x���g���[�̊O�g�ƕ����̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH/2,DXE_WINDOW_HEIGHT/2,0),INVENTORY_WIGHT,INVENTORY_HEIGHT,true,0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawStringEx(INVENTORY_POS.x, INVENTORY_POS.y, -1, "������");
	//�X���b�g�̕`��
	for (auto slot : m_slot) {
		slot->Draw();
		slot->Explanation();
	}
	
}

//------------------------------------------------------------------------------------------------------------
//�A�C�e���̏���������ăC���x���g���[�ɔ��f�����鏈��
bool Inventory::IsCanGetItem(const std::shared_ptr<Item>&item) {
	//item����n��
	auto getitem = m_slot.begin();
	while (getitem != m_slot.end()) {
		if ((*getitem)->getSlotValid() == false) {
			(*getitem)->setSlotValid(true);
			(*getitem)->setSlotHandle(item->getUIHdl());
			(*getitem)->setSlotExlanation(item->getExplanation());
			(*getitem)->setSlotItemType(item->getType());
			return true;
		}
		else if ((*getitem)->getSlotItemType() == item->getType()) {
			//�����𑝂₷
			int num = (*getitem)->getSlotNum();
			num++;
			(*getitem)->setSlotNum(num);
			return true;
		}

		getitem++;
	}
	return false;
}


