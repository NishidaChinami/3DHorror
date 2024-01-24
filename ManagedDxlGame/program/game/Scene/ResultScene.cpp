#include "../dxlib_ext/dxlib_ext.h"
#include"ResultScene.h"
#include"../Manager/Manager.h"
#include"../Mylibrary/Conversion.h"
#include"PlayScene.h"
#include"TitleScene.h"


ResultScene::ResultScene()
{
	m_deathgpc_hdl = LoadGraph("graphics/horrortegami.jpg");
	m_cleargpc_hdl = LoadGraph("graphics/22443712.jpg");
	auto mgr = GameManager::GetInstance();
	mgr->is_switch = false;
	if (mgr->can_clear) {
		letter = CLEAR;
		m_backgroud_hdl = m_cleargpc_hdl;
	}
	else {
		letter = DEATH;
		m_backgroud_hdl = m_deathgpc_hdl;
	}

}

ResultScene::~ResultScene()
{
	DeleteGraph(m_deathgpc_hdl);
	DeleteGraph(m_cleargpc_hdl);
}

void ResultScene::Update(float delta_time)
{
	auto mgr = GameManager::GetInstance();
	if (cf::IntersectMouse(TITLE_POS, LETTER_SIZE)) {
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
			mgr->ChangeScene(std::make_shared<TitleScene>());
		}
	}
	if (cf::IntersectMouse(REPLAY_POS, LETTER_SIZE)) {
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
			mgr->ChangeScene(std::make_shared<PlayScene>());
		}
	}
}

void ResultScene::Draw()
{
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1, 1, m_backgroud_hdl, true);
	DrawStringEx(CENTER_POS.x, CENTER_POS.y, -1, "%s", letter.c_str());
	
	DrawStringEx(TITLE_POS.x, TITLE_POS.y, -1, "%s", SERECT[0].c_str());
	DrawStringEx(REPLAY_POS.x, REPLAY_POS.y, -1, "%s", SERECT[1].c_str());
	
}
