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
	//●との当たり判定を取って、触ってる間横にスライドするとその分丸の位置が動く
	//その大きさをとって数値に代入→それを２５５で換算する値の変化に条件づけ
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