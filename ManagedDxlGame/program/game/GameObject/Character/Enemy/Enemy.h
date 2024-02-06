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

//-------------------------------------------------------------------------------------------------//
//敵クラス
// 当たったら即死
// 視野と聴覚でプレイヤーを追跡
// 通常はアイテムの位置を取得し、最短経路でランダムに周回
//-------------------------------------------------------------------------------------------------//
class Enemy : public GameObject
{
public:
	//Enemyの生成する座標とメディエータークラスを引数にもつ
	Enemy(tnl::Vector3 pos,const std::shared_ptr<Mediator>&mediator);
	~Enemy();
	//Enemyの更新
	void Update(float delta_time)override;
	//Enemyの描画
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	//視野内かを判定する関数
	bool WithinView();
	//プレイヤーの音が鳴ったかを判別
	bool Hearing();
	//壁との当たり判定
	//void StageCorrection(const std::shared_ptr<StageWall>& stagewall);
	
	//プレイヤーと接触したときの処理
	void GameoverEvent();
	

	//ルート決め
	//第1引数 経路探索を始めるグリッド座標
	//第2引数 ゴールのグリッド座標
	//第3引数 Nodeクラス（一マス）の二次元配列ポインタ
	//第4引数 マップの行数
	//第5引数 マップの列数
	//ret 最短経路のベクターを返す
 	void Routing(tnl::Vector2i start, tnl::Vector2i goal, std::vector<astar::Node*>* _route, int row, int col);
	
	
	//--------------------------Getter/Setter------------------------//
	bool getChaseState() const{ return chase_state; }
	tnl::Vector3 getEnemyPos() const{ return mesh->pos_; }
	tnl::Vector3 getEnemySize() const{ return size; }

private:
	//Enemyの移動状態を管理するシークエンス
	tnl::Sequence<Enemy> sequence_ = tnl::Sequence<Enemy>(this, &Enemy::seqPatrol);

	//各移動状態
	bool seqRotate(const float delta_time);			//回転処理
	bool seqMovement(const float delta_time);		//移動処理
	bool seqUpdatePoint(const float delta_time);	//目的地の更新
	bool seqPatrol(const float delta_time);			//ランダムにアイテムの場所を取得し、最短経路探索
	bool seqTrack(const float delta_time);			//プレイヤーへの最短経路探索
	bool seqPlayerDeath(const float delta_time);	//ゲームオーバーの処理


	//MV1modelのハンドル
	int m_model_enemy;
	//modelのtextureハンドル
	int m_texture_enmey;
	//Enemyのスピード
	float m_speed = 0.0f;
	//一フレーム前の位置
	tnl::Vector3 m_prev_pos;
	//Nodeのステートを扱う2次元配列
	astar::Node nodes[Stage::STAGE_ROW][Stage::STAGE_COL];
	//最短経路を保存するベクターポインタ
	std::vector<astar::Node*>route;
	//最短経路アルゴリズムから取得するベクターを取り出すための添え字変数
	int m_index = 0;
	//次に向かいたい場所
	tnl::Vector3 m_next_target;
	//チェイス状態かどうかのフラグ
	bool chase_state = false;

	//------------他クラスの参照用ポインタ------------------------//
	//メディエーターの参照ポインタ
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//経路探索クラスを使えるようにするためのポインタ
	std::shared_ptr<astar::Path>path = nullptr;

	//----------------------定数------------------------//
	//音の聞こえる半径
	const float HEAR_RANGE = 3000;
	//音の聞かれる範囲
	const float HEARED_RANGE = 1000;
	//プレイヤーを追いかけるときの速度
	const float CHASE_SPEED = 10.0f;
	//巡回中の速度
	const float PATROL_SPEED = 5.0;
};
