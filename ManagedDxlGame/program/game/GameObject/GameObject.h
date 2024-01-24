#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class GameCamera;

class GameObject
{
public:
	GameObject() {};
	virtual~GameObject() {};
	virtual void Draw(std::shared_ptr<GameCamera>gamecamera) {}
	virtual void Update(float delta_time) {}
	//stageがセッターができない！
	std::shared_ptr<dxe::Mesh>mesh = nullptr;

	 inline tnl::Vector3 GetObjectSize() const{ return size; }
protected:
	Shared<dxe::Texture> texture = nullptr;
	tnl::Vector3 size = { 0,0,0 };
	bool is_alive = true;
private:

};
