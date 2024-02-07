#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"
#include"../GameObject.h"

class GameCamera;
class Mediator;

//-------------------------------------------------------------------------------------------------//
//�X�e�[�W�̕ǃN���X
// �����蔻����v�Z���邽�߂̃N���X
//-------------------------------------------------------------------------------------------------//
class StageWall : public GameObject
{
public:
	StageWall() {};
	//�������W,���������}�b�v�̃X�e�[�g,���f�B�G�[�^�[�N���X�������ɂ���
	StageWall(const tnl::Vector3 &pos, maze::StageState state, const std::shared_ptr<Mediator>&mediator);
	//�������W�������Ɏ���
	StageWall(const tnl::Vector3 &pos);
	~StageWall() {};
	//�X�V����
	void Update(float delta_time)override{}
	//�`�揈��
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//�S�[���������̏���
	void Goal();

	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	const tnl::Vector3 GetStageWallPos() { return mesh->pos_; }

	//�X�e�[�W�̈�}�X�ڂ̈ʒu
	static const tnl::Vector3 START_BLOCK_POS;
	//�ǂ̕�
	static const int BLOCKSIZE = 400;
	//�ǂ̍���
	static const int BLOCKHIGHT = 800;
private:
	//�X�e�[�W�̃X�e�[�g
	maze::StageState m_state;
	//��t���[���O�̍��W
	//tnl::Vector3 m_prev_pos;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//------------------------�萔------------------------//
	//�S�[���̕�����\������͈�
	const float RANGE = 400;
	//�S�[���O�̕����̍��W
	const tnl::Vector3 MESS_POS = { 500,300,0 };
};
