#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Slot;
class Item;
//-------------------------------------------------------------------------------------------------//
//�v���C���[�̃C���x���g���[
//-------------------------------------------------------------------------------------------------//
class Inventory
{
public:
	Inventory();
	~Inventory();
	//�A�C�e���̏���������ăC���x���g���[�ɔ��f�����鏈��
	bool IsCanGetItem(const std::shared_ptr<Item>&item);
	//�C���x���g���[�̕`��
	void Draw();
private:
	//�X���b�g�̃|�C���^
	std::vector<std::shared_ptr<Slot>>m_slot;

	//------------------------------�萔------------------------------------------//
	//�C���x���g���[�̊O�g�̃T�C�Y
	const float INVENTORY_WIGHT = 600;
	const float INVENTORY_HEIGHT = 220;
	tnl::Vector3 INVENTORY_POS = { 370,280,0 };
};

