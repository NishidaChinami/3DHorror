
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include"Manager/Manager.h"
#include"Scene/PlayScene.h"
#include"Scene/TitleScene.h"
#include"Scene/TurorialScene.h"
#include"Scene/ResultScene.h"
#include"UI/OptionParam.h"
#include"GameObject/Stage/BackGroundStage.h"
#include"Effect/Sound/Sound.h"


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	//シングルトンを実装したクラスのインスタンス生成
	GameManager::GetInstance(std::make_shared<TitleScene>());
	OptionParam::GetInstance();
	Sound::GetInstance();
	SetWindowText("うしろの正面…だあれ？");



}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	//Managerの更新
	GameManager::GetInstance()->Update(delta_time);
	//音量調整
	Sound::GetInstance()->ChangeVolume();
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	GameManager::Destroy();
	OptionParam::Destroy();
	Sound::Destroy();
	
}
