#include "../dxlib_ext/dxlib_ext.h"
#include"maze.h"



/// <summary>
/// ���@��@�̃A���S���Y��
/// </summary>
namespace maze {
	//�@���n�_��ۑ�����x�N�^�[
	static std::vector<tnl::Vector2i> candig;

	//���@�蕔��
	//��1�����@�@��鉡�񐔂���
	//��2�����@�@���c�񐔂���
	//��3����  �}�b�v�̉���
	//��4�����@�}�b�v�̏c��
	//��5�����@�}�b�v�̃X�e�[�g�̂Q�����z��̃|�C���^
	void MazeDig(int x, int y, int row, int col, StageState** state) {
		tnl::Vector2i vec;
		int random = rand()%8, counter = 0;

		//�S�����̂����@���ӏ��������_���Ŏ擾
		while (counter < 4)
		{
			switch ((random + counter) % 4)
			{
			case 0:vec = { 0,-2}; break;
			case 1:vec = { -2,0}; break;
			case 2:vec = { 0,2}; break;
			case 3:vec = { 2,0}; break;

			default:vec = { 0,0}; break;
			}
			//�������l���}�b�v���ł���΁A�ʂ̕�����I��
			if (x + vec.x <= 0 || y + vec.y <= 0 || x + vec.x >= row - 1 || y + vec.y >= col - 1) {
				counter++;
			}
			//����ɂ��łɓ��ł���΁A�ʂ̕�����I��
			else if (state[x + vec.x][y + vec.y] == StageState::Empty) {
				counter++;
			}
			//�@���ӏ��ł���΁A���̂P�}�X��ƂQ�}�X��𓹂ɕϊ�
			else if (state[x + vec.x][y + vec.y] == StageState::Wall) {
				state[x + vec.x][y + vec.y] = StageState::Empty;
				state[x + vec.x / 2][y + vec.y / 2] = StageState::Empty;
				x += vec.x;
				y += vec.y;
				//�����_���Ȓl�����߂Ȃ���
				counter = 0;
				random = rand() % 8;
			}
		}
			return;

	}

	//x(���̏ꍇrow),y(���̏ꍇcol)�̒l���L�����m�F����i�z��O�łȂ����j
	bool Valid(int x, int y, int row,int col,StageState** state) {
		
		if (x < 0 || x >= row) return false;
		if (y < 0 || y >= col) return false;

		if (state[x][y] == StageState::Wall) return true;

		return false;


	}


	//���ł���ꏊ�̒��Ō@���ꏊ���x�N�^�[�ɓ����
	void CanDigPoint(int row, int col, StageState** state) {
		for (int i = 1; i < row - 1; i += 2) {
			for (int j = 1; j < col - 1; j += 2) {
				if (state[i][j] != StageState::Empty)continue;
				////�������O�ǂɋy�ԏꍇ�̓u���C�N
				else if (i == row - 2 && j == col - 2)break;
				
				if (Valid(i - 2, j,row,col, state)
					|| Valid(i, j - 2,row,col, state)
					|| Valid(i + 2, j, row,col,state)
					|| Valid(i, j + 2, row,col,state))candig.emplace_back(tnl::Vector2i(i, j));
				
			}
		}
	}
	
	//�@��Ȃ��Ȃ����|�C���g���x�N�^�[����폜����
	void ReCheckList(int row,int col,StageState** state) {

		auto it = candig.begin();

		while (it != candig.end()) {

			if (Valid((*it).x - 2, (*it).y, row,col,state)
				|| Valid((*it).x, (*it).y - 2, row,col,state)
				|| Valid((*it).x + 2, (*it).y, row,col,state)
				|| Valid((*it).x, (*it).y + 2, row,col,state))it++;
			else {
				it = candig.erase(it);
			}
		}
	}

	//���H���쐬����֐�
	void MazeCreate(int row, int col, StageState** state) {
		//���ׂĂ�ǂɂ���
		int length = 0;
		int index = 0;
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				state[r][c] = StageState::Wall;
			}
		}
		//�ŏ��Ɉ�}�X���ɂ���
		state[1][1] = StageState::Empty;


		while (true) {
			//�@���ꏊ���擾
			CanDigPoint(row, col, state);
			//�擾���Ă����ꏊ���@��Ȃ��Ȃ��Ă��Ȃ����m�F
			ReCheckList(row, col,state);
			//�@���ꏊ���Ȃ��Ȃ����珈���I��
			length = candig.size();
			if (length == 0)break;
			srand((unsigned int)time(nullptr));
			index = int(rand()) % length;
			//�T���J�n
			MazeDig(candig[index].x, candig[index].y, row, col, state);
		}
	}
	void BreakMaze(int row, int col, StageState** state) {

		int counter = 0;
		while (counter < 5)
		{
			int r = rand() % (row - 2) + 1;
			int c = rand() % (col - 2) + 1;
			if (state[r][c] != StageState::Wall)continue;
			//���E�ǂŏ㉺��
			if (state[r + 1][c] == StageState::Wall
				&& state[r - 1][c] == StageState::Wall
				&& state[r][c + 1] == StageState::Empty
				&& state[r][c - 1] == StageState::Empty) {
				state[r][c] = StageState::Empty;
				counter++;
			}
			//���E���ŏ㉺��
			else if (state[r + 1][c] == StageState::Empty
				&& state[r - 1][c] == StageState::Empty
				&& state[r][c + 1] == StageState::Wall
				&& state[r][c - 1] == StageState::Wall) {
				state[r][c] = StageState::Empty;
				counter++;
			}

		}

		//�Ń����_����5�ӏ����ɂ���
	}

	//�X�^�[�g�ƃS�[�������߂�
	void MakeGoal(int row, int col, StageState** state) {
		state[1][1] = StageState::Start;

		while (true)
		{
			int random = rand() % (row - 2) + 1;
			if (random % 2) {
				if (state[row - 2][random] == StageState::Empty) {
					state[row - 1][random] = StageState::Goal;
					break;
				}
			}
			else {
				if (state[random][col - 2] == StageState::Empty) {
					state[random][col - 1] = StageState::Goal;
					break;
				}
			}
		}
	}
}


	

