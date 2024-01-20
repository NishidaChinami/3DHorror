#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace maze
{

	enum class StageState {
		Empty,
		Wall,
		Start,
		Goal,
		Key,
		None
	};

	//���@�蕔��
	//��1�����@�@��鉡�񐔂���
	//��2�����@�@���c�񐔂���
	//��3����  �}�b�v�̉���
	//��4�����@�}�b�v�̏c��
	//��5�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	bool MapCheck(int x, int z, int row, int col);

	//x,y�̒l���L�����m�F����i�z��O�łȂ����j
	//��1�����@�z������m���߂������񐔂���
	//��2�����@�z������m���߂����c�񐔂���
	//��3����  �}�b�v�̉���
	//��4�����@�}�b�v�̏c��
	//��5�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	void MazeDig(int x, int z, int row, int col, StageState** state);

	//���ł���ꏊ�̒��Ō@���ꏊ���x�N�^�[�ɓ����
	//��1����  �}�b�v�̉���
	//��Q�����@�}�b�v�̏c��
	//��R�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	void CanDigPoint(int row, int col, StageState** state);

	//�@��Ȃ��Ȃ����|�C���g���x�N�^�[����폜����
	//��1����  �}�b�v�̉���
	//��Q�����@�}�b�v�̏c��
	//��R�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	void ReCheckList(StageState** state);

	//���H�����֐�
	//��1����  �}�b�v�̉���
	//��Q�����@�}�b�v�̏c��
	//��R�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	void MazeCreate(int row, int col, StageState** state);

	void MakeGoal(int row, int col, StageState** state);
	void BreakMaze(int row, int col, StageState** state);

};
