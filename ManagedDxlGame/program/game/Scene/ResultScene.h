#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	//�V�[���̍X�V
	void Update(float delta_time)override;
	//�V�[���̕`��֐�
	void Draw()override;
private:

};

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}