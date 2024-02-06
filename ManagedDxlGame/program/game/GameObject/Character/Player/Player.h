#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject.h"

class GameCamera;
class Mediator;
class StageWall;
class Flashlight;
class Sound;

//-------------------------------------------------------------------------------------------------//
//�v���C���[�N���X
// ���[�U�[�����삷��
//-------------------------------------------------------------------------------------------------//

class Player : public GameObject
{
public:
	Player() {};
	//�`��p�̃J�����N���X�ƃI�u�W�F�N�g�̎Q�Ɛ�������f�B�G�[�^�[�N���X�������ɂ���
	Player(std::shared_ptr<GameCamera>gamecamera, const std::shared_ptr<Mediator>&mediator);
	~Player();
	//�X�V����
	void Update(float delta_time)override;
	//�`�揈��
	void Draw(std::shared_ptr<GameCamera>gamecamera) override {}
	//���񂾂Ƃ��̊֐�
	void GameoverEvent();
	//�X�e�[�W�Ɠ��������Ƃ��̏���
	void StageCorrection(const std::shared_ptr<StageWall>& stagewall);

	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(tnl::Vector3, PlayerPos, mesh->pos_);
	tnl::Quaternion getPlayerRot()const{ return mesh->rot_; }
	tnl::Vector3 getPlayerSize() const { return size; }
	float getPlayerSpeed()const { return m_speed; }
	float getPlayerStamina() const { return m_stamina; }
	bool getPlayerDash()const { return m_can_dash; }

	static const int MAXSTAMINA = 1200;
private:
	//�v���C���[�̈ړ���Ԃ��Ǘ�����V�[�N�G���X
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqWalk);
	//�e�ړ����
	bool seqWalk(const float delta_time);	//�����ړ�
	bool seqRun(const float delta_time);	//����ړ�
	bool seqSneek(const float delta_time);	//���Ⴊ�݈ړ�
	bool seqDeath(const float delta_time);	//���S����
	
	// �v���C���[�̈ړ����x
	float m_speed = 0;
	//��t���[���O�̈ʒu
	tnl::Vector3 m_prev_pos;
	//����Ƃ��̃X�^�~�i
	int m_stamina = 0;
	//����邩�ǂ����̃t���O
	bool m_can_dash = true;

	//�������`���[�g���A���ƃ��C���Q�[���Ő؂�ւ��邽�߂̕ϐ�
	std::string m_walk_sound;
	std::string m_run_sound;


	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Flashlight>m_flashlight = nullptr;
	std::shared_ptr<GameCamera>m_gamecamera = nullptr;
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//----------------------�萔------------------------//
	//���鑬�x
	const float DASH_SPEED = 10;
	//�������x
	const float WALK_SPEED = 4;
	//���Ⴊ�ݑ��x
	const float WALK_SNEEK = 2;
	//��J��Ԃ̃X�^�~�i���l
	const float TIREDNESS = 10;
	
};

