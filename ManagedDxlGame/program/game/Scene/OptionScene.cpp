#include "../dxlib_ext/dxlib_ext.h"
#include"OptionScene.h"

OptionScene::OptionScene()
{

}

OptionScene::~OptionScene()
{
}

void OptionScene::Update(float delta_time) {
	sequence_.Update(delta_time);
	//���Ƃ̓����蔻�������āA�G���Ă�ԉ��ɃX���C�h����Ƃ��̕��ۂ̈ʒu������
	//���̑傫�����Ƃ��Đ��l�ɑ����������Q�T�T�Ŋ��Z����l�̕ω��ɏ����Â�
}

void OptionScene::Draw() {
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxEx(tnl::Vector3(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0), INVENTORY_WIGHT, INVENTORY_HEIGHT, true, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);*/
}

bool OptionScene::seqOption(float delta_time) {
	return true;
}
bool OptionScene::seqIdle(float delta_time) {
	return true;
}

//auto mgr = GameManager::GetInstance();