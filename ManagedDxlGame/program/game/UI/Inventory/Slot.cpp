
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Slot.h"
#include"Inventory.h"


Slot::Slot(const tnl::Vector3 &pos)
{
	m_pos = pos;
}

Slot::~Slot()
{
}

void Slot::Draw() {
	//UIÇÃï`âÊ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//slotîwåi
	DrawBoxEx(m_pos, SLOTSIZE, SLOTSIZE, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (m_is_valid) {
		DrawRotaGraph(m_pos.x, m_pos.y, 0.6, 1, m_ui_hdl, true);
		if(m_number >=2)DrawStringEx(m_pos.x + 25, m_pos.y + 25, -1, "%d", m_number);
	}
}


//ê‡ñæï∂ÇÃï\é¶
void Slot::Explanation() {
	if (m_is_valid) {
		if (cf::IntersectMouse(m_pos, tnl::Vector3(SLOTSIZE, SLOTSIZE, 0))) {
			DrawStringEx(m_pos.x, m_pos.y + 50, -1, "%s", m_explanation.c_str());
		}
	}
}