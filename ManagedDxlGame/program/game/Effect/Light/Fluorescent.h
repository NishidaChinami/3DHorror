#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/GameObject.h"


class GameCamera;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//�I�u�W�F�N�g�N���X
//�ق��̃I�u�W�F�N�g�̐e�N���X
// ���b�V���̃|�C���^��T�C�Y�A���W�Ȃǂ������o�ϐ��ɂ���
//-------------------------------------------------------------------------------------------------//
class Fluorescent : public GameObject
{
public:
	//�������W�Ƒ��I�u�W�F�N�g�̎Q�Ƃ������f�B�G�[�^�[�N���X�������Ɏ���
	Fluorescent(const tnl::Vector3 &pos, const std::shared_ptr<Mediator>&mediator);
	~Fluorescent();
	//�X�V����
	void Update(float delta_time)override;
	//�`�揈��
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//���̓_�ŏ���
	void Blink(float delta_time);

	
private:
	//�u�����̃n���h��
	int m_fluorescent_hdl;

	float m_range = 4000;			//���C�g�̗L������
	//���������p�����[�^�[
	float m_atten0 = 0;				//���C�g�̒��_�̋����Ɋ֌W�Ȃ��������闦���w�肷��
	float m_atten1 = 0.0009;		//���C�g�̋����ɔ�Ⴕ�Č������闦
	float m_atten2 = 0.0000f;		//���C�g�̋����̓��ɔ�Ⴕ�Č������闦

	//�_�ł̑��x�ϐ�
	float m_trans_time =0;
	//�_�ł̃J�E���g
	float m_blink_count = 0;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Mediator>m_mediator = nullptr;

	//----------------------�萔------------------------//
	//�_�ł̊Ԋu
	const float SECONDS = 45;
	//�d���̃��b�V���̃T�C�Y
	const int LIGHT_SIZE = 10;
	//�G�Ƃ̋߂��𔻒肷��͈�
	const int RANGE = 800;
	//�u�����̌��̒ʏ푬�x
	const float TRANS_TIME = 2.0f;
	//���x�̕ω��͈̔�
	const int TRANS_RANGE = 6;
};

