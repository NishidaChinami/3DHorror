#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"


class Player;
class StageWall;
class GameCamera;
class Stage;
class Enemy;
class Item;
class Inventory;
class Message;
class BackGroundStage;

//-------------------------------------------------------------------------------------------------//
//���f�B�G�[�^�[�N���X
// �I�u�W�F�N�g�̎Q�Ɛ����ɏW�񂷂����
// ���f�B�G�^�[�p�^�[���������������������A���ۂ̓f�[�^�[�}�l�[�W���̂悤�ȓ��������Ă���
//-------------------------------------------------------------------------------------------------//
class Mediator
{
public:
	Mediator() {
		m_intersect_stage = new tnl::Vector3();
	}
	~Mediator() {
		delete m_intersect_stage;
	}

	//--------------------player��Getter��Setter------------------------------------------------//
	
	//�v���C���[�̍��W
	const tnl::Vector3 &MGetPlayerPos()const;
	//�v���C���[�̉�]
	const tnl::Quaternion &MGetPlayerRot()const;
	//�v���C���[�̃T�C�Y
	const tnl::Vector3 &MGetPlayerSize()const;
	//�v���C���[�̃X�s�[�h
	float MGetPlayerSpeed()const;
	//�v���C���[�̃X�^�~�i
	float MGetPlayerStamina()const;
	//����邩�ǂ����̃t���O
	bool MGetPlayerDash()const;

	//--------------------Enemy��Getter��Setter------------------------------------------------//

	//Enemy�̍��W
	const tnl::Vector3 &MGetEnemyPos()const;
	//Enemy�̃T�C�Y
	const tnl::Vector3 &MGetEnemySize()const;
	//�v���C���[�������Ă��邩�ǂ����̃t���t
	bool MGetChaseState()const;

	//--------------------�X�e�[�W��Getter��Setter------------------------------------------------//
	//stage��stagestate�Q�����z��̎擾
	//��1���� ��
	//��2���� �s��
	//ret ���̃}�X�̖��H�X�e�[�g��Ԃ�
	const maze::StageState &MGetStageState(int r, int c)const;
	//Ray���X�e�[�W�̕ǂɂԂ����_�Ɣ�r�Ώۂ̌�_�̂ǂ��炪�߂����𔻒肷��
	//��1�����@Ray���o�����̂̍��W
	//��2�����@Ray�̌���
	//��3�����@��r�Ώۂ̌�_���W
	//ret �ǂ��߂��ꍇtrue ��r�Ώۂ��߂��ꍇfalse��Ԃ�
	bool MGetIntersectStage(const tnl::Vector3 &pos, const tnl::Vector3 &ray, tnl::Vector3 *intersect_point )const;

	//-------------------�A�C�e����Getter��Setter------------------------------------------------//
	
	//Item�̈ʒu���擾
	const std::vector<tnl::Vector2i> &MGetItemPos();
	//�t���b�s�[�f�B�X�N��5���W�܂������ǂ����̃t���O
	bool MGetItemFloopy()const;
	//�L����ǂ�ł��邩�̃t���O
	bool MGetReadArticle ()const;
	void MSetReadArticle(bool read);

	//-------------------���b�Z�[�W��Getter��Setter------------------------------------------------//
	//�\�����郁�b�Z�[�W�̏���o�^����
	void MSetMessage(int title);
	//���̃X�g�[���[���擾����
	int MGetTitleType()const;

	//-------------------�C���x���g���[��Getter��Setter------------------------------------------------//
	//�A�C�e���̏����C���x���g���[�̓n��
	bool MSetPassInventory(const std::shared_ptr<Item>& item);

	//skybox�̃p�����[�^�[�̐ݒ�
	void MSetSkyEmissive(tnl::Vector3 &param);
	const tnl::Vector3 &MGetSkyEmissive()const;

	//-------------------���f�B�G�[�^�[�N���X�ɕK�v�ȃN���X�̃|�C���^------------------------------------------------//
	void SetPlayerClass(std::shared_ptr<Player>&player) { m_player = player; }
	void SetStageClass(std::shared_ptr<Stage>&stage) { m_stage = stage; }
	void SetEnemyClass(std::shared_ptr<Enemy>&enemy) { m_enemy = enemy; }
	void SetItemClass(std::list<std::shared_ptr<Item>>& item) { for (auto list : item) { m_item_list.emplace_back(list); } }
	void SetTutorialItemClass(std::list<std::shared_ptr<Item>>& tutorial_item) { for (auto list : tutorial_item) { m_tutorialitem_list.emplace_back(list); } }
	void SetMessageClass(std::shared_ptr<Message>& message) { m_message = message; }
	void SetInventoryClass(std::shared_ptr<Inventory>& inventory) { m_inventory = inventory; }
	void SetBackGroundClass(std::shared_ptr<BackGroundStage>& background) { m_backgroundstage = background; }
	void SetStageWallClass(std::list<std::shared_ptr<StageWall>>& stagewall) { for (auto list : stagewall) { m_stagewall_list.emplace_back(list); } }


	void MSetLightParam(bool light) { m_getlight = light; }
	bool MGetLightParam()const { return m_getlight; }
private:
	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	//���ݎQ�Ƃ�h�����߂�weak_ptr���g�p
	std::weak_ptr<Player>m_player;
	std::weak_ptr<GameCamera>m_camera;
	std::weak_ptr<Stage>m_stage;
	std::weak_ptr<Enemy>m_enemy;
	std::list<std::weak_ptr<Item>>m_item_list;
	std::list<std::weak_ptr<Item>>m_tutorialitem_list;
	std::weak_ptr<Message>m_message;
	std::weak_ptr<Inventory>m_inventory;
	std::weak_ptr<BackGroundStage>m_backgroundstage;
	std::list<std::weak_ptr<StageWall>>m_stagewall_list;
	//���C�g���Q�b�g�������ǂ���
	bool m_getlight = false;

	//��_�̃|�C���^
	tnl::Vector3* m_intersect_stage = nullptr;
};
