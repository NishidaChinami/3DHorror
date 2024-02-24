#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;

//-------------------------------------------------------------------------------------------------//
//�X�e�[�W�̎������������s����N���X
//-------------------------------------------------------------------------------------------------//
class Stage
{
public:
	Stage();
	~Stage();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	const maze::StageState &getStgaeState(int r,int c) const{ return m_state[r][c]; }

	//-----------------�ÓI�萔--------------------------------//
	//���������}�b�v�̗񐔁E�s��
	const static int STAGE_ROW = 15;
	const static int STAGE_COL = 15;
private:
	//�X�e�[�W�̃X�e�[�g�z��
	maze::StageState m_state[STAGE_ROW][STAGE_COL];
};


