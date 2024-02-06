#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;
class Mediator;

//-------------------------------------------------------------------------------------------------//
//ステージの壁クラス
// 当たり判定を計算するためのクラス
//-------------------------------------------------------------------------------------------------//
class StageWall : public GameObject
{
public:
	StageWall() {};
	//生成座標,自動生成マップのステート,メディエータークラスを引数にもつ
	StageWall(const tnl::Vector3 &pos, maze::StageState state, const std::shared_ptr<Mediator>&mediator);
	//生成座標を引数に持つ
	StageWall(const tnl::Vector3 &pos);
	~StageWall() {};
	//更新処理
	void Update(float delta_time)override{}
	//描画処理
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//ゴールした時の処理
	void Goal();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	const tnl::Vector3 GetStageWallPos() { return mesh->pos_; }

	//ステージの一マス目の位置
	static const tnl::Vector3 START_BLOCK_POS;
	//壁の幅
	static const int BLOCKSIZE = 400;
	//壁の高さ
	static const int BLOCKHIGHT = 800;
private:
	//ステージのステート
	maze::StageState m_state;
	//一フレーム前の座標
	//tnl::Vector3 m_prev_pos;

	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//------------------------定数------------------------//
	//ゴールの文字を表示する範囲
	const float RANGE = 400;
	//ゴール前の文字の座標
	const tnl::Vector3 MESS_POS = { 500,300,0 };
};
