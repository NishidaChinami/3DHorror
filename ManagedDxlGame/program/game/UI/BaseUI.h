#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class BaseUI
{
public:
	BaseUI() {};
	virtual ~BaseUI() {};
	virtual void Update(float delta_time) {};//�V�[���̍X�V
	virtual void Draw() {};//�V�[���̕`��֐�
private:

};

