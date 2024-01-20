
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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	
	GameManager::GetInstance(std::make_shared<PlayScene>());
	OptionParam::GetInstance();
	SetWindowText("������̐��ʁc������H");



}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	GameManager::GetInstance()->Update(delta_time);
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	GameManager::Destroy();
}
