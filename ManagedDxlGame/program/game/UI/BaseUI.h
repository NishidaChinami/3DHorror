#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class BaseUI
{
public:
	BaseUI() {};
	virtual ~BaseUI() {};
	virtual void Update(float delta_time) {};//シーンの更新
	virtual void Draw() {};//シーンの描画関数
private:

};

