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
class BackGroudStage;

//-------------------------------------------------------------------------------------------------//
//���f�B�G�[�^�[�N���X
// �I�u�W�F�N�g�̎Q�Ɛ����ɏW�񂷂����
//-------------------------------------------------------------------------------------------------//
class Mediator
{
public:
	Mediator() {};
	~Mediator() {};

	//--------------------player��Getter��Setter------------------------------------------------//
	
	//�v���C���[�̍��W
	tnl::Vector3 MGetPlayerPos();
	//�v���C���[�̉�]
	tnl::Quaternion MGetPlayerRot();
	//�v���C���[�̃T�C�Y
	tnl::Vector3 MGetPlayerSize();
	//�v���C���[�̃X�s�[�h
	float MGetPlayerSpeed();
	//�v���C���[�̃X�^�~�i
	float MGetPlayerStamina();
	//����邩�ǂ����̃t���O
	bool MGetPlayerDash();

	//--------------------Enemy��Getter��Setter------------------------------------------------//

	//Enemy�̍��W
	tnl::Vector3 MGetEnemyPos();
	//Enemy�̃T�C�Y
	tnl::Vector3 MGetEnemySize();
	//�v���C���[�������Ă��邩�ǂ����̃t���t
	bool MGetChaseState();

	//--------------------�X�e�[�W��Getter��Setter------------------------------------------------//
	//stage��stagestate�Q�����z��̎擾
	//��1���� ��
	//��2���� �s��
	//ret ���̃}�X�̖��H�X�e�[�g��Ԃ�
	maze::StageState MGetStageState(int r, int c);

	//-------------------�A�C�e����Getter��Setter------------------------------------------------//
	
	//Item�̈ʒu���擾
	std::vector<tnl::Vector2i> MGetItemPos();
	//�t���b�s�[�f�B�X�N��5���W�܂������ǂ����̃t���O
	bool MGetItemFloopy();
	//�L����ǂ�ł��邩�̃t���O
	bool MGetReadArticle ();
	void MSetReadArticle(bool read);

	//-------------------���b�Z�[�W��Getter��Setter------------------------------------------------//
	//�\�����郁�b�Z�[�W�̏���o�^����
	void MSetMessage(int title);
	//���̃X�g�[���[���擾����
	int MGetTitleType();

	//-------------------�C���x���g���[��Getter��Setter------------------------------------------------//
	//�A�C�e���̏����C���x���g���[�̓n��
	bool MSetPassInventory(const std::shared_ptr<Item>& item);

	//skybox�̃p�����[�^�[�̐ݒ�
	void MSetSkyEmissive(tnl::Vector3 param);
	tnl::Vector3 MGetSkyEmissive();

	//-------------------���f�B�G�[�^�[�N���X�ɕK�v�ȃN���X�̃|�C���^------------------------------------------------//
	void SetPlayerClass(const std::shared_ptr<Player>&player) { m_player = player; }
	void SetStageClass(const std::shared_ptr<Stage>&stage) { m_stage = stage; }
	void SetStageWallClass(const std::list<std::shared_ptr<StageWall>>& stagewall) { m_stagewall_list= stagewall; }
	void SetEnemyClass(std::shared_ptr<Enemy>&enemy) { m_enemy = enemy; }
	void SetItemClass(const std::list<std::shared_ptr<Item>>& item) { m_item_list = item; }
	void SetTutorialItemClass(const std::list<std::shared_ptr<Item>>& tutorial_item) { m_tutorialitem_list = tutorial_item; }
	void SetMessageClass(const std::shared_ptr<Message>& message) { m_message = message; }
	void SetInventoryClass(const std::shared_ptr<Inventory>& inventory) { m_inventory = inventory; }
	void SetBackGroundClass(const std::shared_ptr<BackGroudStage>& background) { m_backgroundstage = background; }

	void MSetLightParam(bool light) { m_getlight = light; }
	bool MGetLightParam() { return m_getlight; }
private:
	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Player>m_player = nullptr;
	std::list<std::shared_ptr<StageWall>>m_stagewall_list;
	std::shared_ptr<GameCamera>m_camera = nullptr;
	std::shared_ptr<Stage>m_stage = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<Item>>m_item_list;
	std::list<std::shared_ptr<Item>>m_tutorialitem_list;
	std::shared_ptr<Message>m_message = nullptr;
	std::shared_ptr<Inventory>m_inventory = nullptr;
	std::shared_ptr<BackGroudStage>m_backgroundstage = nullptr;

	//���C�g���Q�b�g�������ǂ���
	bool m_getlight = false;


};
