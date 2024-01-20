
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include"Manager/Manager.h"
#include"Scene/PlayScene.h"
#include"Scene/TitleScene.h"
#include"UI/MainUI.h"
#include"UI/OptionParam.h"


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	
	GameManager::GetInstance(std::make_shared<PlayScene>());
	OptionParam::GetInstance();
	SetWindowText("うしろの正面…だあれ？");



}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	GameManager::GetInstance()->Update(delta_time);
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	GameManager::Destroy();
}
