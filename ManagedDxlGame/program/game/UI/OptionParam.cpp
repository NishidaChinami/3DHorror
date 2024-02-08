#include "../dxlib_ext/dxlib_ext.h"
#include"OptionParam.h"

//------------------------------------------------------------------------------------------------------------
//インスタンス生成
OptionParam* OptionParam::GetInstance() {
	static OptionParam* instance = nullptr;
	if (!instance) {
		instance = new OptionParam();
	}
	return instance;
}
//------------------------------------------------------------------------------------------------------------
//デストラクタ関数
void OptionParam::Destroy() {
	delete GetInstance();
}


