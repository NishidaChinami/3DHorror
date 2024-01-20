#pragma once
#include "../library/tnl_sequence.h"

class BaseScene;
class BaseUI;

//-------------------------------------------------------------------------------------------------//
//マネージャークラス

//-------------------------------------------------------------------------------------------------//
class GameManager {
public:
	//マネージャーのインスタンス取得
	static GameManager* GetInstance(std::shared_ptr<BaseScene>start_scene = nullptr);
	//デストラクタ関数
	static void Destroy();
	//シーン切り替え用の関数
	void ChangeScene(std::shared_ptr<BaseScene>next_scene, float trans_time = 0.5f);
	
	//マネージャーの更新関数
	void Update(float delta_time);
private:

	GameManager(std::shared_ptr<BaseScene>start_scene);
	//シーン切り替え用のポインタ変数
	std::shared_ptr<BaseScene>now_scene_ = nullptr;
	std::shared_ptr<BaseScene>next_scene_ = nullptr;



	
	//フェードアウト用の黒画像のハンドル
	int tansition_graph_hdl = 0;

	//フェードの速度変数
	float trans_time_ = 0.5f;

	//フェードインフェードアウト用
	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);
	//フェードイン
	bool seqTransIn(const float delta_time);
	//フェードアウト
	bool seqTransOut(const float delta_time);
	//待機状態
	bool seqRunScene(const float delta_time);

};