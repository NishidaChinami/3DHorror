//#pragma once
//#include "../dxlib_ext/dxlib_ext.h"
//#include"BaseScene.h"
//
//
//class Collision;
//
//class TutorialStage;
//
//class TutorialScene : public BaseScene
//{
//public:
//	TutorialScene();
//	~TutorialScene();
//
//	void Update(float delta_time)override;//プレイシーンの更新関数
//	void Draw()override;			//プレイシーンの描画関数
//	void CollisionFunc() {};
//
//private:
//
//	std::shared_ptr<Collision>collision = nullptr;
//	Shared<dxe::ShadowMap> shadow = nullptr;
//
//	
//	std::list<std::shared_ptr<TutorialStage>> tutorialstage;
//
//
//	Shared<dxe::Mesh> skybox = nullptr;
//	
//};
//
////