#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


class Factory;
class Collision;
class Player;
class Enemy;
class StageWall;
class MainUI;
class SubScene;
class OptionScene;
class Sound;

//-------------------------------------------------------------------------------------------------//
// ���C���v���C��ʂ̃N���X
//-------------------------------------------------------------------------------------------------//
class PlayScene final : public BaseScene, public std::enable_shared_from_this<PlayScene> {
public:

	PlayScene();
	~PlayScene()override;
	//�X�V����
	void Update(float delta_time)override;
	//�`�揈��
	void Draw()override;
	//BGM�Đ��֐�
	void PlayBGM();
	//�����蔻�����鏀�����s���֐�
	void CollisionFuc();

	//�q�N���X�̒ǉ�
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}

private:
	//�V�[����Ԃ̃V�[�P���X
	tnl::Sequence<PlayScene> sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::seqMainGame);
	bool seqMainGame(float delta_time);					//�Q�[���̃v���C���
	bool seqOpenUI(float delta_time);					//UI���J���Ă���Ƃ��̏��
	//bool seqIdle(float delta_time) { return true; }		//�ҋ@���

	//�Q�[���I�[�o�[���̌��̃O���t�B�b�N�n���h��
	int m_gameover_gpc_hdl = 0;

	//�e�N���X�̃��X�g
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//�q�N���X�̃|�C���^
	std::shared_ptr<SubScene>m_subscene;
	std::shared_ptr<OptionScene>m_option;
	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Factory>m_factory = nullptr;
	std::shared_ptr<Collision>m_collision = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<StageWall>> m_stagewall;

	//bool m_alive_tutorial = false;
};