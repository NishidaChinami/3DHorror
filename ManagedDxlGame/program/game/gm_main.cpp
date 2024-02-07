
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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	//�V���O���g�������������N���X�̃C���X�^���X����
	GameManager::GetInstance(std::make_shared<TitleScene>());
	OptionParam::GetInstance();
	Sound::GetInstance();
	SetWindowText("������̐��ʁc������H");



}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	//Manager�̍X�V
	GameManager::GetInstance()->Update(delta_time);
	//���ʒ���
	Sound::GetInstance()->ChangeVolume();
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	GameManager::Destroy();
	OptionParam::Destroy();
	Sound::Destroy();
	
}
