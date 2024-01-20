#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;


class Stage
{
public:
	Stage();
	~Stage();

	void Draw(std::shared_ptr<GameCamera>gamecamera);

	const static int m_row = 15;
	const static int  m_col = 15;


	const maze::StageState GetStgaeState(int r,int c) { return m_state[r][c]; }
private:
	int m_map[m_row][m_col];
	maze::StageState m_state[m_row][m_col];
	
	
	
};


