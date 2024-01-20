#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject.h"

class GameCamera;
class Mediator;
class StageWall;
class Flashlight;
class Sound;

/// <summary>
/// ���[�U�[�����삷��v���C���[�N���X
/// </summary>

class Player : public GameObject
{
public:
	Player() {};
	Player(std::shared_ptr<Sound>sound, std::shared_ptr<GameCamera>gamecamera);
	~Player();

	void Update(float delta_time)override;
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	//���񂾂Ƃ��̊֐�
	void Death() {};
	//�X�e�[�W�Ɠ��������Ƃ��̊֐�
	void StageCorrection(const std::shared_ptr<StageWall>& stagewall);

	tnl::Vector3 GetPlayerPos()const { return mesh->pos_; }
	void SetPlayerPos(tnl::Vector3& pos) { mesh->pos_; }
	tnl::Quaternion GetPlayerRot() { return mesh->rot_; }
	tnl::Vector3 GetPlayerSize() const { return size; }
	float GetPlayerSpeed()const { return m_speed; }
	float GetPlayerStamina() const { return m_stamina; }

private:
	//�v���C���[�̈ړ���Ԃ��Ǘ�����V�[�N�G���X
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqWalk);
	//�e�ړ����
	bool seqWalk(const float delta_time);
	bool seqRun(const float delta_time);
	bool seqEvent(const float delta_time);
	bool seqSneek(const float delta_time);
	//bool seqHide(const float delta_time);
	// 
	// �v���C���[�̈ړ����x
	float m_speed = 0;
	//���鑬�x
	const float m_dash_speed = 10;
	//�������x
	const float m_walk_speed = 3;
	//��t���[���O�̈ʒu
	tnl::Vector3 m_prev_pos;
	//����Ƃ��̃X�^�~�i
	int m_stamina = 1000;
	bool m_can_dash = true;
	//�T�E���h���Ǘ�����u�[��
	bool m_play_sound = false;
	bool m_switch_sound = false;

	//�����d���̃|�C���^
	std::shared_ptr<Flashlight>m_flashlight = nullptr;
	//�T�C���h�̃|�C���^
	std::shared_ptr<Sound>m_sound = nullptr;
	std::shared_ptr<GameCamera>m_player_camera = nullptr;

	
	
	
};

