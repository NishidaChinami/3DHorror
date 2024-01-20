#pragma once
#include "../library/tnl_sequence.h"

class BaseScene;
class BaseUI;

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
private:

	GameManager(std::shared_ptr<BaseScene>start_scene);
	//�V�[���؂�ւ��p�̃|�C���^�ϐ�
	std::shared_ptr<BaseScene>now_scene_ = nullptr;
	std::shared_ptr<BaseScene>next_scene_ = nullptr;



	
	//�t�F�[�h�A�E�g�p�̍��摜�̃n���h��
	int tansition_graph_hdl = 0;

	//�t�F�[�h�̑��x�ϐ�
	float trans_time_ = 0.5f;

	//�t�F�[�h�C���t�F�[�h�A�E�g�p
	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);
	//�t�F�[�h�C��
	bool seqTransIn(const float delta_time);
	//�t�F�[�h�A�E�g
	bool seqTransOut(const float delta_time);
	//�ҋ@���
	bool seqRunScene(const float delta_time);

};