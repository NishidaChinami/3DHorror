#pragma once
#include "../library/tnl_sequence.h"

class BaseScene;

//-------------------------------------------------------------------------------------------------//
//�}�l�[�W���[�N���X
//-------------------------------------------------------------------------------------------------//
class GameManager {
public:
	//�}�l�[�W���[�̃C���X�^���X�擾
	static GameManager* GetInstance(std::shared_ptr<BaseScene>start_scene = nullptr);
	//�f�X�g���N�^�֐�
	static void Destroy();
	//�V�[���؂�ւ��p�̊֐�
	void ChangeScene(std::shared_ptr<BaseScene>next_scene, float trans_time = 0.5f);
	//�}�l�[�W���[�̍X�V�֐�
	void Update(float delta_time);
	//�Q�[�����N���A�ł�����
	bool can_clear = false;
	//�V�[����؂�ւ�������bool
	bool is_switch = false;
	//�`���[�g���A�������C���Q�[�����̃t���O
	bool is_tutorial = true;
private:
	GameManager(std::shared_ptr<BaseScene>start_scene);
	//�t�F�[�h�C���t�F�[�h�A�E�g�p�V�[�P���X
	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);
	bool seqTransIn(const float delta_time);//�t�F�[�h�C��
	bool seqTransOut(const float delta_time);//�t�F�[�h�A�E�g
	bool seqRunScene(const float delta_time);//�ҋ@���

	//�V�[���؂�ւ��p�̃|�C���^�ϐ�
	std::shared_ptr<BaseScene>now_scene_ = nullptr;
	std::shared_ptr<BaseScene>next_scene_ = nullptr;
	
	//�t�F�[�h�A�E�g�p�̍��摜�̃n���h��
	int tansition_graph_hdl = 0;
	//�t�F�[�h�̑��x�ϐ�
	float trans_time_ = 0.5f;

};