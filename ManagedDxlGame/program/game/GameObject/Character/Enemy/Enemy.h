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
	//����p���쐬����֐�
	void CreatRay(std::shared_ptr<GameCamera>gamecamera);
	//��������𔻒肷��֐�
	bool WithinView();
	//�v���C���[�̉����������𔻕�
	bool Hearing();

	//���[�g����
	void Routing(tnl::Vector2i start, tnl::Vector2i goal, std::vector<astar::Node*>* _route, int row, int col);
	
	//�v���C���[�̈ړ���Ԃ��Ǘ�����V�[�N�G���X
	tnl::Sequence<Enemy> sequence_ = tnl::Sequence<Enemy>(this, &Enemy::seqPatrol);

	//�e�ړ����
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

	//�T�E���h�̃|�C���^�ϐ�
	std::shared_ptr<Sound>m_sound;
	//Node�̃X�e�[�g������2�����z��
	astar::Node nodes[Stage::m_row][Stage::m_col];
	std::vector<astar::Node*>route;

	//�o�H�T���N���X���g����悤�ɂ��邽�߂̃|�C���^
	std::shared_ptr<astar::Path>path = nullptr;

	//�ŒZ�o�H�A���S���Y������擾����x�N�^�[�����o�����߂̓Y�����ϐ�
	int m_index = route.size();
	//���Ɍ����������ꏊ
	tnl::Vector3 m_next_target;
	//�`�F�C�X��Ԃ��ǂ����̃t���O
	bool chase_state = false;
	bool can_hear = false;
	//����p�̊p�x��ۑ����郊�X�g
	tnl::Vector3 ray;

	//���̕������锼�a
	const float RADIUS_RUN = 1000;
	const float RADIUS_WALK = 600;
	//�f�o�b�N�p
	bool debug = false;
};
