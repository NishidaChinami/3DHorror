
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
//-------------------Manager file------------------------//
#include"Manager/Manager.h"
//-------------------Scene file------------------------//
#include"Scene/PlayScene.h"
#include"Scene/TitleScene.h"
#include"Scene/TutorialScene.h"
#include"Scene/ResultScene.h"
//-------------------UI file------------------------//
#include"UI/OptionParam.h"
//-------------------Effect file------------------------//
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
	tnl::AddFontTTF("font/g_comichorrorR_freeR.ttf");
	tnl::AddFontTTF("font/HinaMincho-Regular.ttf");
	tnl::AddFontTTF("font/ShipporiMinchoB1-Regular.ttf");


}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	//Managerの更新
	GameManager::GetInstance()->Update(delta_time);
	//音量調整
	Sound::GetInstance()->ChangeVolume();
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	GameManager::Destroy();
	OptionParam::Destroy();
	Sound::Destroy();
	
}
