#include "../dxlib_ext/dxlib_ext.h"
#include"Stage.h"
#include"../Camera/GameCamera.h"


Stage::Stage() {
	maze::StageState* tmp_state[m_row];
	for (int i = 0; i < m_row; ++i) {
		tmp_state[i] = m_state[i];
	}
	maze::MazeCreate(m_row, m_col, tmp_state);
	maze::MakeGoal(m_row, m_col, tmp_state);
	maze::BreakMaze(m_row, m_col, tmp_state);

	
};
Stage::~Stage() {};

