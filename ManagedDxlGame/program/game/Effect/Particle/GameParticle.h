#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class GameCamera;

class GameParticle
{
public:
	GameParticle();
	~GameParticle();
	//�`�揈��
	void Draw(std::shared_ptr<GameCamera>gamecamera);
private:
	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	//�p�[�e�B�N�����g�����߂̃|�C���^
	std::list<std::shared_ptr<dxe::Particle>> m_ptcl_list;
};

