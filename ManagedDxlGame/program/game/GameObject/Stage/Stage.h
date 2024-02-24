#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;

//-------------------------------------------------------------------------------------------------//
//ステージの自動生成を実行するクラス
//-------------------------------------------------------------------------------------------------//
class Stage
{
public:
	Stage();
	~Stage();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	const maze::StageState &getStgaeState(int r,int c) const{ return m_state[r][c]; }

	//-----------------静的定数--------------------------------//
	//自動生成マップの列数・行数
	const static int STAGE_ROW = 15;
	const static int STAGE_COL = 15;
private:
	//ステージのステート配列
	maze::StageState m_state[STAGE_ROW][STAGE_COL];
};


