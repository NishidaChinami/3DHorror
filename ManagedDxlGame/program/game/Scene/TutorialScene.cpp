//#include "../dxlib_ext/dxlib_ext.h"
//#include"TurorialScene.h"
//#include"../Manager/Factory.h"
//#include"../GameObject/Camera/GameCamera.h"
//#include"../GameObject/GameObject.h"
//#include"../GameObject/Collision/Collision.h"
//#include"../GameObject/Character/Player/Player.h"
//#include"../GameObject/Item/Item.h"
//#include"../Effect/Sound/Sound.h"
//
//
//TutorialScene::TutorialScene()
//{
//	SetFogEnable(true);
//	SetFogColor(32, 32, 32);
//	SetFogStartEnd(500.0f, 1500.0f);
//	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
//	SetBackgroundColor(32, 32, 32);
//
//	skybox = dxe::Mesh::CreateCubeMV(30000, 20, 20);
//	skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_c.png"));
//	skybox->loadMaterial("material.bin");
//
//}
//
//TutorialScene::~TutorialScene()
//{
//}
//
//void TutorialScene::Update(float delta_time) {
//	skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));
//	
//	skybox->drawGuiMaterialControlloer();
//	
//
//	//for (auto groud : factory->GetClassBackGroudStage()) {
//	//	groud->Draw(factory->GetClassCamera());
//	//}
//	/*for (auto obj : factory->GetClassObj()) {
//		obj->Draw(factory->GetClassCamera());
//		obj->Update(delta_time);
//	}*/
//	//‘S“–‚½‚è”»’è‚ðŒŸ’m
//	/*for (auto li : collision->intersect_list_) {
//		if (tnl::IsIntersectAABB(li.a_->mesh->pos_, li.a_->size, li.b_->mesh->pos_, li.b_->size)) {
//			li.intersected_call_(li.a_, li.b_);
//		}
//	}*/
//}
//
//void TutorialScene::Draw() {
//
//}