#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

class Factory;
class Collision;
class Player;
class StageWall;
class SubScene;
class OptionScene;
class GameParticle;
//-------------------------------------------------------------------------------------------------//
// �`���[�g���A���X�e�[�W�̃N���X
//-------------------------------------------------------------------------------------------------//
class TutorialScene : public BaseScene
{
public:
	TutorialScene();
	~TutorialScene();
	//�X�V����
	void Update(float delta_time)override;
	//�`�揈��
	void Draw()override;
	//�����蔻�����鏀�����s���֐�
	void CollisionFunc();

	//�q�N���X�̒ǉ�
	void AddChild(std::shared_ptr<BaseScene>child) {
		m_child_list.emplace_back(child);
	}

private:
	//�V�[����Ԃ̃V�[�P���X
	tnl::Sequence<TutorialScene> sequence_ = tnl::Sequence<TutorialScene>(this, &TutorialScene::seqMainGame);
	bool seqMainGame(float delta_time);	//�Q�[���̃v���C���
	bool seqOpenUI(float delta_time);	//UI���J���Ă���Ƃ��̏��

	//�e�N���X�̃��X�g��p��
	std::list<std::shared_ptr<BaseScene>>m_child_list;
	//�q�N���X�̃|�C���^
	std::shared_ptr<SubScene>m_subscene;
	std::shared_ptr<OptionScene>m_option;
	//�V���h�E�}�b�v�|�C���^
	Shared<dxe::ShadowMap> m_shadow = nullptr;
	//�p�[�e�B�N���|�C���^
	Shared<GameParticle>particle = nullptr;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Collision>collision = nullptr;
	std::shared_ptr<Factory>m_factory = nullptr;
	std::shared_ptr<Collision>m_collision = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::list<std::shared_ptr<StageWall>> m_stagewall;
	//--------------�萔--------------------------//
	const int FONT_SIZE = 18;
};
