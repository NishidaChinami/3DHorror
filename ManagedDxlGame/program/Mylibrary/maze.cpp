#include "../dxlib_ext/dxlib_ext.h"
#include"maze.h"



/// <summary>
/// 穴掘り法のアルゴリズム
/// </summary>
namespace maze {
	//掘れる地点を保存するベクター
	static std::vector<tnl::Vector2i> candig;

	//穴掘り部分
	//第1引数　掘れる横列数を代入
	//第2引数　掘れる縦列数を代入
	//第3引数  マップの横列数
	//第4引数　マップの縦列数
	//第5引数　マップのステートの２次元配列のポインタ
	void MazeDig(int x, int y, int row, int col, StageState** state) {
		tnl::Vector2i vec;
		int random = rand()%8, counter = 0;

		//４方向のうち掘れる箇所をランダムで取得
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
			//足した値がマップ内であれば、別の方向を選択
			if (x + vec.x <= 0 || y + vec.y <= 0 || x + vec.x >= row - 1 || y + vec.y >= col - 1) {
				counter++;
			}
			//さらにすでに道であれば、別の方向を選択
			else if (state[x + vec.x][y + vec.y] == StageState::Empty) {
				counter++;
			}
			//掘れる箇所であれば、その１マス先と２マス先を道に変換
			else if (state[x + vec.x][y + vec.y] == StageState::Wall) {
				state[x + vec.x][y + vec.y] = StageState::Empty;
				state[x + vec.x / 2][y + vec.y / 2] = StageState::Empty;
				x += vec.x;
				y += vec.y;
				//ランダムな値を決めなおし
				counter = 0;
				random = rand() % 8;
			}
		}
			return;

	}

	//x(この場合row),y(この場合col)の値が有効か確認する（配列外でないか）
	bool Valid(int x, int y, int row,int col,StageState** state) {
		
		if (x < 0 || x >= row) return false;
		if (y < 0 || y >= col) return false;

		if (state[x][y] == StageState::Wall) return true;

		return false;


	}


	//道である場所の中で掘れる場所をベクターに入れる
	void CanDigPoint(int row, int col, StageState** state) {
		for (int i = 1; i < row - 1; i += 2) {
			for (int j = 1; j < col - 1; j += 2) {
				if (state[i][j] != StageState::Empty)continue;
				////調査が外壁に及ぶ場合はブレイク
				else if (i == row - 2 && j == col - 2)break;
				
				if (Valid(i - 2, j,row,col, state)
					|| Valid(i, j - 2,row,col, state)
					|| Valid(i + 2, j, row,col,state)
					|| Valid(i, j + 2, row,col,state))candig.emplace_back(tnl::Vector2i(i, j));
				
			}
		}
	}
	
	//掘れなくなったポイントをベクターから削除する
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

	//迷路を作成する関数
	void MazeCreate(int row, int col, StageState** state) {
		//すべてを壁にする
		int length = 0;
		int index = 0;
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				state[r][c] = StageState::Wall;
			}
		}
		//最初に一マス道にする
		state[1][1] = StageState::Empty;


		while (true) {
			//掘れる場所を取得
			CanDigPoint(row, col, state);
			//取得していた場所が掘れなくなっていないか確認
			ReCheckList(row, col,state);
			//掘れる場所がなくなったら処理終了
			length = candig.size();
			if (length == 0)break;
			srand((unsigned int)time(nullptr));
			index = int(rand()) % length;
			//探索開始
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
			//左右壁で上下道
			if (state[r + 1][c] == StageState::Wall
				&& state[r - 1][c] == StageState::Wall
				&& state[r][c + 1] == StageState::Empty
				&& state[r][c - 1] == StageState::Empty) {
				state[r][c] = StageState::Empty;
				counter++;
			}
			//左右道で上下壁
			else if (state[r + 1][c] == StageState::Empty
				&& state[r - 1][c] == StageState::Empty
				&& state[r][c + 1] == StageState::Wall
				&& state[r][c - 1] == StageState::Wall) {
				state[r][c] = StageState::Empty;
				counter++;
			}

		}

		//でランダムに5箇所道にする
	}

	//スタートとゴールを決める
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


	

