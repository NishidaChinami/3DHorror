#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"maze.h"

namespace astar {


	// マップステータス
	// 経路探索用ノード
	enum class TrackState {
		OPEN,
		CLOSED,
		ROAD,      // 道
		NONE,
		START,      // スタート
		END       // ゴール
	};

	class Node {
	public:
		Node() :
			status(TrackState::NONE),
			cost_real(0),
			cost_guess(0),
			score(0),
			parent(nullptr)
		{}


		tnl::Vector2i pos;  // 2次元配列上の座標
		TrackState status;//自動生成マップからStateをとる
		int cost_real;     // 実コスト
		int cost_guess;    // 推定コスト
		int score;         // スコア
		Node* parent;      // 親ノード( 最後にゴールから辿るため )

		bool operator < (const Node& node) const {
			return score > node.score;
		}

	};

	class Path
	{
	public:
		Path() {};
		~Path() {};

		// 指定座標が有効な( OPEN 可能な )マップ位置かどうか判定
		//第1引数 調べたい座標
		//第２引数　Nodeクラスの２次元配列ポインタ
		//第3・4引数　最短経路を求めたいマップの横と縦列の数
		bool IsEnableMapPosition(tnl::Vector2i pos, Node** _nodes,int row,int col);

		// [ 現在オープンになっているノードで一番スコアの小さいものを取得 ]
		// サンプルの分かり易さ優先なので全ノードを調べる形にしているが、
		// 効率は良くないのでライブラリ化する時にでも 既にオープンしている
		// ノードだけ調べるように効率化を図った方がよい
		Node* GetSmallScoreNodeFromOpenNodes(Node** _nodes, int row, int col);


		// 経路探索 Astarアルゴリズム
		bool Aster(Node** _nodes, Node* _now, std::vector<Node*>* _route,int row ,int col);


	};


}