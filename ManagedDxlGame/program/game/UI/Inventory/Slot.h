#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/Item/Item.h"

class Slot
{
public:
	Slot(const tnl::Vector3 &pos);
	~Slot();
	//�`��
	void Draw();

	//�������̕\��
	void Explanation();

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
private:
	tnl::Vector3 m_pos;

	const float SLOTSIZE = 100;
};

