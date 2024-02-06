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
//�G�N���X
// ���������瑦��
// ����ƒ��o�Ńv���C���[��ǐ�
// �ʏ�̓A�C�e���̈ʒu���擾���A�ŒZ�o�H�Ń����_���Ɏ���
//-------------------------------------------------------------------------------------------------//
class Enemy : public GameObject
{
public:
	//Enemy�̐���������W�ƃ��f�B�G�[�^�[�N���X�������ɂ���
	Enemy(tnl::Vector3 pos,const std::shared_ptr<Mediator>&mediator);
	~Enemy();
	//Enemy�̍X�V
	void Update(float delta_time)override;
	//Enemy�̕`��
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	//��������𔻒肷��֐�
	bool WithinView();
	//�v���C���[�̉����������𔻕�
	bool Hearing();
	//�ǂƂ̓����蔻��
	//void StageCorrection(const std::shared_ptr<StageWall>& stagewall);
	
	//�v���C���[�ƐڐG�����Ƃ��̏���
	void GameoverEvent();
	

	//���[�g����
	//��1���� �o�H�T�����n�߂�O���b�h���W
	//��2���� �S�[���̃O���b�h���W
	//��3���� Node�N���X�i��}�X�j�̓񎟌��z��|�C���^
	//��4���� �}�b�v�̍s��
	//��5���� �}�b�v�̗�
	//ret �ŒZ�o�H�̃x�N�^�[��Ԃ�
 	void Routing(tnl::Vector2i start, tnl::Vector2i goal, std::vector<astar::Node*>* _route, int row, int col);
	
	
	//--------------------------Getter/Setter------------------------//
	bool getChaseState() const{ return chase_state; }
	tnl::Vector3 getEnemyPos() const{ return mesh->pos_; }
	tnl::Vector3 getEnemySize() const{ return size; }

private:
	//Enemy�̈ړ���Ԃ��Ǘ�����V�[�N�G���X
	tnl::Sequence<Enemy> sequence_ = tnl::Sequence<Enemy>(this, &Enemy::seqPatrol);

	//�e�ړ����
	bool seqRotate(const float delta_time);			//��]����
	bool seqMovement(const float delta_time);		//�ړ�����
	bool seqUpdatePoint(const float delta_time);	//�ړI�n�̍X�V
	bool seqPatrol(const float delta_time);			//�����_���ɃA�C�e���̏ꏊ���擾���A�ŒZ�o�H�T��
	bool seqTrack(const float delta_time);			//�v���C���[�ւ̍ŒZ�o�H�T��
	bool seqPlayerDeath(const float delta_time);	//�Q�[���I�[�o�[�̏���


	//MV1model�̃n���h��
	int m_model_enemy;
	//model��texture�n���h��
	int m_texture_enmey;
	//Enemy�̃X�s�[�h
	float m_speed = 0.0f;
	//��t���[���O�̈ʒu
	tnl::Vector3 m_prev_pos;
	//Node�̃X�e�[�g������2�����z��
	astar::Node nodes[Stage::STAGE_ROW][Stage::STAGE_COL];
	//�ŒZ�o�H��ۑ�����x�N�^�[�|�C���^
	std::vector<astar::Node*>route;
	//�ŒZ�o�H�A���S���Y������擾����x�N�^�[�����o�����߂̓Y�����ϐ�
	int m_index = 0;
	//���Ɍ����������ꏊ
	tnl::Vector3 m_next_target;
	//�`�F�C�X��Ԃ��ǂ����̃t���O
	bool chase_state = false;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	//���f�B�G�[�^�[�̎Q�ƃ|�C���^
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//�o�H�T���N���X���g����悤�ɂ��邽�߂̃|�C���^
	std::shared_ptr<astar::Path>path = nullptr;

	//----------------------�萔------------------------//
	//���̕������锼�a
	const float HEAR_RANGE = 3000;
	//���̕������͈�
	const float HEARED_RANGE = 1000;
	//�v���C���[��ǂ�������Ƃ��̑��x
	const float CHASE_SPEED = 10.0f;
	//���񒆂̑��x
	const float PATROL_SPEED = 5.0;
};
