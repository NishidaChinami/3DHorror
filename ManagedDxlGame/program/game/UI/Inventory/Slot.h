#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/Item/Item.h"

//-------------------------------------------------------------------------------------------------//
//�v���C���[�̃C���x���g���[
//-------------------------------------------------------------------------------------------------//
class Slot
{
public:
	Slot(const tnl::Vector3 &pos):m_pos(pos){}
	~Slot();
	//�`�揈��
	void Draw();
	//�������̕\���̏���
	void Explanation();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	TNL_PROPERTY(int, SlotHandle, m_ui_hdl);
	TNL_PROPERTY(int, SlotNum, m_number);
	TNL_PROPERTY(std::string, SlotExlanation, m_explanation);
	TNL_PROPERTY(bool, SlotValid, m_is_valid);
	TNL_PROPERTY(Item::ItemType, SlotItemType, m_itemtype);

private:
	//�X���b�g�̒��Ɉڂ�摜�n���h��
	int m_ui_hdl = 0;
	//�\�������
	int m_number = 1;
	//������
	std::string m_explanation;
	//���������Ă��邩�ǂ���
	bool m_is_valid = false;
	//�A�C�e���^�C�v
	Item::ItemType m_itemtype;
	//�擾�����A�C�e����UI�摜�̂QD���W
	tnl::Vector3 m_pos;
	//�X���b�g�̘g�̃T�C�Y
	const float SLOTSIZE = 100;
};

