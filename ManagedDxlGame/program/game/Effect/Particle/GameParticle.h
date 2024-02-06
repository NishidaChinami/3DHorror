#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class GameCamera;

class GameParticle
{
public:
	GameParticle();
	~GameParticle();
	//描画処理
	void Draw(std::shared_ptr<GameCamera>gamecamera);
private:
	//------------他クラスの参照用ポインタ------------------------//
	//パーティクルを使うためのポインタ
	std::list<std::shared_ptr<dxe::Particle>> m_ptcl_list;
};

