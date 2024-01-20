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
class Sound;

//-------------------------------------------------------------------------------------------------//
//Scene�̎q�N���X
// 
// �v���C��ʂ̃N���X
//-------------------------------------------------------------------------------------------------//
class PlayScene final : public BaseScene, public std::enable_shared_from_this<PlayScene> {
public:

	PlayScene();
	~PlayScene()override;
	//�v���C�V�[���̍X�V�֐�
	void Update(float delta_time)override;
	//�v���C�V�[���̕`��֐�
	void Draw()override;

	void PlayBGM();
	
	void CollitionFuc();
	void MainGameCollision();
	void TutorialCollision();

	//�R���|�W�b�g�p�^�[��
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}
	

private:
	//�e�N���X�̃��X�g��p��
	std::list<std::shared_ptr<BaseScene>>m_child_list;

	//�V�[���J�ڗp�̃e���v���[�g
	tnl::Sequence<PlayScene> sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::seqSetMainGame);
	//���ʉ�ʂ܂��̓X�^�[�g��ʂɖ߂�
	bool seqResult(float delta_time) { return true; }

	bool seqSetTutorial(float delta_time);
	bool seqSetMainGame(float delta_time);
	
	bool seqMainGame(float delta_time);

	bool seqOpenUI(float delta_time);

	//�V�[�P���X�Ń`�F�C�X�Ƃ��C�x���g����
	std::shared_ptr<SubScene>m_subscene;

	std::shared_ptr<Factory>m_factory = nullptr;
	std::shared_ptr<Collision>m_collision = nullptr;
	Shared<dxe::ShadowMap> m_shadow = nullptr;
	std::shared_ptr<Sound>m_sound = nullptr;

	std::shared_ptr<Player> m_player = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<StageWall>> m_stagewall;

	Shared<dxe::Mesh> m_skybox = nullptr;

	int ShadowMapHandle;

	bool m_alive_tutorial = false;
};