#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;
class Mediator;

class StageWall : public GameObject
{
public:
	StageWall() {};
	StageWall(tnl::Vector3 pos, maze::StageState state, std::shared_ptr<dxe::Mesh> cloneBox, const std::shared_ptr<Mediator>mediator);
	StageWall(tnl::Vector3 pos, std::shared_ptr<dxe::Mesh> cloneBox);
	~StageWall() {};
	void Update(float delta_time)override {}
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	void Goal();
	static const int BLOCKSIZE = 400;
	static const int BLOCKHIGHT = 800;

	const tnl::Vector3 GetStageWallPos() { return mesh->pos_; }

	static const tnl::Vector3 START_BLOCK_POS;

private:
	maze::StageState m_state;
	tnl::Vector3 m_prev_pos;
	std::shared_ptr<Mediator>m_mediator = nullptr;
};
