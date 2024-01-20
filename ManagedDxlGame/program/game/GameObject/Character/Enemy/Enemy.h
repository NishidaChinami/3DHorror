#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject.h"
#include"../Mylibrary/maze.h"
#include"../Mylibrary/astar.h"
#include"../../Stage/StageParts.h"
#include"../../Stage/Stage.h"

class GameCamera;
class Mediator;
class Sound;

class Enemy : public GameObject
{
public:
	Enemy(tnl::Vector3 pos,const std::shared_ptr<Mediator>mediator,std::shared_ptr<Sound>sound);
	~Enemy();
	void EnemyMove() {};

	void Update(float delta_time)override;
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//視野角を作成する関数
	void CreatRay(std::shared_ptr<GameCamera>gamecamera);
	//視野内かを判定する関数
	bool WithinView();
	//プレイヤーの音が鳴ったかを判別
	bool Hearing();

	//ルート決め
	void Routing(tnl::Vector2i start, tnl::Vector2i goal, std::vector<astar::Node*>* _route, int row, int col);
	
	//プレイヤーの移動状態を管理するシークエンス
	tnl::Sequence<Enemy> sequence_ = tnl::Sequence<Enemy>(this, &Enemy::seqPatrol);

	//各移動状態
	bool seqRotate(const float delta_time);
	bool seqMovement(const float delta_time);
	bool seqUpdatePoint(const float delta_time);
	bool seqPatrol(const float delta_time);
	bool seqTrack(const float delta_time);

	bool GetChaseState() { return chase_state; }
	tnl::Vector3 GetEnemyPos() { return mesh->pos_; }
	tnl::Vector3 GetEnemySize() { return size; }

private:
	float m_speed = 0.0f;
	const float CHASE_SPEED = 8.0f;
	const float PATROL_SPEED = 5.0;
	int m_model_enemy;
	int m_texture_enmey;
	//tnl::Vector3 m_pos;
	std::shared_ptr<Mediator>m_mediator = nullptr;

	//サウンドのポインタ変数
	std::shared_ptr<Sound>m_sound;
	//Nodeのステートを扱う2次元配列
	astar::Node nodes[Stage::m_row][Stage::m_col];
	std::vector<astar::Node*>route;

	//経路探索クラスを使えるようにするためのポインタ
	std::shared_ptr<astar::Path>path = nullptr;

	//最短経路アルゴリズムから取得するベクターを取り出すための添え字変数
	int m_index = route.size();
	//次に向かいたい場所
	tnl::Vector3 m_next_target;
	//チェイス状態かどうかのフラグ
	bool chase_state = false;
	bool can_hear = false;
	//視野角の角度を保存するリスト
	tnl::Vector3 ray;

	//音の聞こえる半径
	const float RADIUS_RUN = 1000;
	const float RADIUS_WALK = 600;
	//デバック用
	bool debug = false;
};
