#pragma once
//-------------------------------------------------------------------------------------------------//
//Sceneの親クラス
//-------------------------------------------------------------------------------------------------//
class BaseScene {
public:
	BaseScene() {};
	virtual~BaseScene() {};
	virtual void Update(float delta_time) {};//シーンの更新
	virtual void Draw() {};//シーンの描画関数
protected:
	Shared<dxe::ScreenEffect> screen_efct = nullptr;
};