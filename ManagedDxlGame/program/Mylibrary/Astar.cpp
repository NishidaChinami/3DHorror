#include "../dxlib_ext/dxlib_ext.h"
#include"Astar.h"
#include"maze.h"

namespace astar {


	// 指定座標が有効な( OPEN 可能な )マップ位置かどうか判定
	bool Path::IsEnableMapPosition(tnl::Vector2i pos, Node** _nodes, int row, int col) {
		if (pos.x < 0) return false;
		if (pos.y < 0) return false;
		if (pos.x >= row) return false;
		if (pos.y >= col) return false;
		if (TrackState::START == _nodes[pos.y][pos.x].status) return false;
		if (TrackState::ROAD == _nodes[pos.y][pos.x].status) return true;
		if (TrackState::END == _nodes[pos.y][pos.x].status) return true;
		return false;
	}


	Node* Path::GetSmallScoreNodeFromOpenNodes(Node** _nodes, int row, int col) {
		Node* p = nullptr;
		for (int i = 0; i < row; ++i) {
			for (int k = 0; k < col; ++k) {
				if (TrackState::OPEN != _nodes[k][i].status) continue;
				if (nullptr == p) p = &_nodes[k][i];
				if (p->score > _nodes[k][i].score) p = &_nodes[k][i];
				else if (p->score == _nodes[k][i].score) {
					if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];
				}
			}
		}
		return p;
	}

	
	bool Path::Aster(Node** _nodes, Node* _now, std::vector<Node*>* _route, int row, int col) {
	

		// スタート地点のスコア計算
		if (TrackState::OPEN == _now->status) {
			_now->score = _now->cost_real + _now->cost_guess;
		}

		// ４方向の座標
		tnl::Vector2i dir[4] = { tnl::Vector2i(0, 1), tnl::Vector2i(1, 0), tnl::Vector2i(0, -1), tnl::Vector2i(-1, 0) };

		// 周り４方向を調べて可能ならオープン
		for (int i = 0; i < 4; ++i) {
			tnl::Vector2i next = _now->pos + dir[i];

			// 調べ先がオープン可能かどうか
			if (!IsEnableMapPosition(next, _nodes,row,col)) continue;

			// オープン予定の座標がゴールだった
			if (TrackState::END == _nodes[next.y][next.x].status) {

				// ゴールを保存して
				(*_route).push_back(&_nodes[next.y][next.x]);

				// ゴール一歩手前から自分の親ノードを遡って記録
				// この記録が最短経路となる
				Node* p = _now;
				while (nullptr != p) {
					(*_route).push_back(p);
					p = p->parent;
				}

				// ゴールが見つかったので true
				return true;
			}

			// ４方向のノードに対するオープンとスコア計算処理
			_nodes[next.y][next.x].status = TrackState::OPEN;
			_nodes[next.y][next.x].parent = _now;
			_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
			_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
		}

		// 周りのオープンが終わったので自分はクローズ
		if (TrackState::START != _now->status) {
			_now->status = TrackState::CLOSED;
		}

		// 現在オープンしているノードで一番スコアの小さいものが基準ノード
		Node* node = GetSmallScoreNodeFromOpenNodes(_nodes,row,col);

		// ノードが見つからなければ到達不能
		if (nullptr == node) return false;

		// 再帰処理
		return Aster(_nodes, node, _route,row,col);

	};


	
}