#pragma once

/*


//-----------------------------------------------------------------------------------------------------------
//
//
// マウスカーソルからレイを飛ばして３次元空間に存在するオブジェクトと衝突判定をとるサンプル
//
//
//-----------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"


Shared<dxe::Camera> camera = nullptr;
Shared<dxe::Mesh> box = nullptr;


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);
	SetDefaultLightParameter("directional_light_parameter.bin");

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	box = dxe::Mesh::CreateCubeMV(100);
	box->setTexture(dxe::Texture::CreateFromFile("graphics/test.jpg"));
	box->pos_ = { -100, 0, 0 };

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// Update
	//
	//-------------------------------------------------------------------------------

	tnl::Vector3 ms = tnl::Input::GetMousePosition();

	tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(ms.x, ms.y, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera->view_, camera->proj_);

	if (tnl::IsIntersectRayAABB(
		camera->pos_
		, ray_nml
		, tnl::ToMaxAABB(box->pos_, { 100, 100, 100 })
		, tnl::ToMinAABB(box->pos_, { 100, 100, 100 }) ) )
	{
		DrawStringEx(0, 0, -1, "hit") ;
	}

	camera->Update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	DrawGridGround(camera, 50, 20);

	box->render(camera);

	DrawDefaultLightGuiController();

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}



*/
