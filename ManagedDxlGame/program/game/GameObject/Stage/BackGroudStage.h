#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class GameCamera;

class BackGroudStage
{
public:
	BackGroudStage(tnl::Vector3 pos,std::shared_ptr<dxe::Mesh> clonePlane, std::shared_ptr<dxe::Mesh> clonePlane2);
	BackGroudStage(tnl::Vector3 pos, std::shared_ptr<dxe::Mesh> clonePlane);
	~BackGroudStage();
	void Draw(std::shared_ptr<GameCamera>gamecamera);

	static const int SIZE = 1600;
private:
	std::shared_ptr<dxe::Mesh>ceiling = nullptr;
	std::shared_ptr<dxe::Mesh>floor = nullptr;
	Shared<dxe::Texture> texture = nullptr;
};

