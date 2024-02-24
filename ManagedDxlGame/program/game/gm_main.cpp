
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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	//�V���O���g�������������N���X�̃C���X�^���X����
	GameManager::GetInstance(std::make_shared<TitleScene>());
	OptionParam::GetInstance();
	Sound::GetInstance();
	SetWindowText("������̐��ʁc������H");
	tnl::AddFontTTF("font/g_comichorrorR_freeR.ttf");
	tnl::AddFontTTF("font/HinaMincho-Regular.ttf");
	tnl::AddFontTTF("font/ShipporiMinchoB1-Regular.ttf");


}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	//Manager�̍X�V
	GameManager::GetInstance()->Update(delta_time);
	//���ʒ���
	Sound::GetInstance()->ChangeVolume();
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	GameManager::Destroy();
	OptionParam::Destroy();
	Sound::Destroy();
	
}
