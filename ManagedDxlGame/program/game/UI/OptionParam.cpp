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


