#pragma once
//-------------------------------------------------------------------------------------------------//
//Sceneの親クラス
//-------------------------------------------------------------------------------------------------//
class BaseScene {
public:
	BaseScene() {};
	virtual~BaseScene() {};
	//シーンの更新
	virtual void Update(float delta_time) {};
	//シーンの描画関数
	virtual void Draw() {};
protected:
	//スクリーンエフェクトのポインタ
	Shared<dxe::ScreenEffect> screen_efct = nullptr;
};