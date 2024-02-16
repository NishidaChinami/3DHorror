
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Slot.h"
#include"Inventory.h"
#include"../../UI/OptionParam.h"


Slot::~Slot()
{
	DeleteGraph(m_ui_hdl);
}
//------------------------------------------------------------------------------------------------------------
//`æ
void Slot::Draw() {
	//UIÌ`æ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//slotwi
	DrawBoxEx(m_pos, SLOTSIZE, SLOTSIZE, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (m_isvalid) {
		DrawRotaGraph(m_pos.x, m_pos.y, DIANETER, 1, m_ui_hdl, true);
		if(m_number >=2)DrawStringEx(m_pos.x + SLOTSIZE/4, m_pos.y + SLOTSIZE / 4, -1, "%d", m_number);
	}
}

//------------------------------------------------------------------------------------------------------------
//à¾¶Ì\¦
void Slot::Explanation() {
	if (m_isvalid) {
		if (cf::IntersectMouse(m_pos, tnl::Vector3(SLOTSIZE, SLOTSIZE, 0))) {
			SetFontSize(SLIOT_FONT);
			cf::DrawCenterString(m_explanation.c_str(),tnl::Vector3(m_pos.x,m_pos.y+ SLOTSIZE/2,0));
		}
	}
}