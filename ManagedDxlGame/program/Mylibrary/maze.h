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

	//穴掘り部分
	//第1引数　掘れる横列数を代入
	//第2引数　掘れる縦列数を代入
	//第3引数  マップの横列数
	//第4引数　マップの縦列数
	//第5引数　マップのステートの２次元配列のポインタ
	bool MapCheck(int x, int z, int row, int col);

	//x,yの値が有効か確認する（配列外でないか）
	//第1引数　配列内か確かめたい横列数を代入
	//第2引数　配列内か確かめたい縦列数を代入
	//第3引数  マップの横列数
	//第4引数　マップの縦列数
	//第5引数　マップのステートの２次元配列のポインタ
	void MazeDig(int x, int z, int row, int col, StageState** state);

	//道である場所の中で掘れる場所をベクターに入れる
	//第1引数  マップの横列数
	//第２引数　マップの縦列数
	//第３引数　マップのステートの２次元配列のポインタ
	void CanDigPoint(int row, int col, StageState** state);

	//掘れなくなったポイントをベクターから削除する
	//第1引数  マップの横列数
	//第２引数　マップの縦列数
	//第３引数　マップのステートの２次元配列のポインタ
	void ReCheckList(StageState** state);

	//迷路を作る関数
	//第1引数  マップの横列数
	//第２引数　マップの縦列数
	//第３引数　マップのステートの２次元配列のポインタ
	void MazeCreate(int row, int col, StageState** state);

	void MakeGoal(int row, int col, StageState** state);
	void BreakMaze(int row, int col, StageState** state);

};
