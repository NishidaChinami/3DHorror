#include "../dxlib_ext/dxlib_ext.h"
#include"OptionParam.h"

//------------------------------------------------------------------------------------------------------------
//�C���X�^���X����
OptionParam* OptionParam::GetInstance() {
	static OptionParam* instance = nullptr;
	if (!instance) {
		instance = new OptionParam();
	}
	return instance;
}
//------------------------------------------------------------------------------------------------------------
//�f�X�g���N�^�֐�
void OptionParam::Destroy() {
	delete GetInstance();
}

void OptionParam::Update()
{
	if (font_size != prev_font_size)SetFontSize(font_size);
	if (font != prev_font) {
		if(font == FontName::NORMAL)ChangeFont("Hina Mincho", DX_CHARSET_DEFAULT);
		if (font == FontName::HORROR)ChangeFont("g_�R�~�b�N�z���[���|-����", DX_CHARSET_DEFAULT);
		if (font == FontName::OPTION)ChangeFont("Shippori Mincho B1", DX_CHARSET_DEFAULT);
	}
	prev_font_size = font_size;
	prev_font = font;
}
