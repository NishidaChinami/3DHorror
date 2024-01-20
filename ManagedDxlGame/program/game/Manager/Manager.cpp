#include "../dxlib_ext/dxlib_ext.h"
#include "Manager.h"
#include"../../game/Scene/BaseScene.h"
#include"../UI/BaseUI.h"

GameManager::GameManager(std::shared_ptr<BaseScene>start_scene) : now_scene_(start_scene) {
	tansition_graph_hdl = LoadGraph("graphics/black.bmp");
}

GameManager* GameManager::GetInstance(std::shared_ptr<BaseScene>start_scene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

void GameManager::Destroy() {
	delete GetInstance();
	
}


void GameManager::ChangeScene(std::shared_ptr<BaseScene>next_scene, float trans_time) {
	
	next_scene_ = next_scene;
	trans_time_ = trans_time;
	sequence_.change(&GameManager::seqTransOut);
}


void GameManager::Update(float delta_time) {
	if (now_scene_) {
		now_scene_->Update(delta_time);
		now_scene_->Draw();
	}
	
	sequence_.Update(delta_time);
}
bool GameManager::seqTransOut(const float delta_time) {
	int alpha = (sequence_.getProgressTime() / trans_time_ * 255.0f * 0.6);//フェードアウトのみ遅延
	if (alpha >= 255) {
		sequence_.change(&GameManager::seqTransIn);
		now_scene_ = nullptr;
		now_scene_ = next_scene_;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}

bool GameManager::seqTransIn(const float delta_time) {
	int alpha = 255 - (sequence_.getProgressTime() / trans_time_ * 255.0f);
	if (alpha <= 0) {
		sequence_.change(&GameManager::seqRunScene);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}


bool GameManager::seqRunScene(const float delta_time) {
	return true;
}
