#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	//シーンの更新
	void Update(float delta_time)override;
	//シーンの描画関数
	void Draw()override;
private:

};

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}