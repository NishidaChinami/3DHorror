#include "../dxlib_ext/dxlib_ext.h"
#include"Stage.h"
#include"../Camera/GameCamera.h"

//------------------------------------------------------------------------------------------------------------
//©“®¶¬‚·‚éŠÖ”‚ğŒÄ‚Ô
Stage::Stage() {
	maze::StageState* tmp_state[STAGE_ROW];
	for (int i = 0; i < STAGE_ROW; ++i) {
		tmp_state[i] = m_state[i];
	}
	maze::MazeCreate(STAGE_ROW, STAGE_COL, tmp_state);
	maze::MakeGoal(STAGE_ROW, STAGE_COL, tmp_state);
	maze::BreakMaze(STAGE_ROW, STAGE_COL, tmp_state);	
};
Stage::~Stage() {

};

