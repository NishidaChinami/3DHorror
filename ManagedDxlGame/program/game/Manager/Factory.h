#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;
class GameObject;
class Player;
class GameCamera;
class Stage;
class StageWall;
class Enemy;
class Item;
class BackGroundStage;
class Sound;
class Fluorescent;
class Inventory;
class Message;

//-------------------------------------------------------------------------------------------------//
//Factory�N���X
// �Q�[���I�u�W�F�N�g�̐����N���X
//-------------------------------------------------------------------------------------------------//
class Factory
{
public:
	Factory();
	~Factory();
	//�I�u�W�F�N�g�N���X�����f�B�G�[�^�[�N���X�ɐݒ肷��
	void SetMediator();
	//���C���Q�[���Ɏg���I�u�W�F�N�g�̐���������֐�
	void CreatMainGame();
	//�`���[�g���A���Q�[���Ɏg���I�u�W�F�N�g�̐���������֐�
	void CreatTutorial();
	//CreatMainGame�Ő��������I�u�W�F�N�g��Object���X�g�ɓ����֐�
	void AddMainObject();
	//CreatTutorial�Ő��������I�u�W�F�N�g��TutorialObject���X�g�֐�
	void AddTutorialObject();

	//--------------------------Getter/Setter------------------------//
	//Factory�Ő��������N���X
	const std::list<std::shared_ptr<GameObject>> &GetClassObj() { return m_object_list; }
	const std::list<std::shared_ptr<GameObject>> &GetClassObj_Tutorial() { return m_object_tutorial_list; }
	const std::shared_ptr<GameCamera>&GetClassCamera() { return m_gamecamera; }
	const std::shared_ptr<Mediator>&GetClassMediator() { return m_mediator; }
	const std::shared_ptr<Player>&GetClassPlayer() { return m_player; }
	const std::shared_ptr<Stage>&GetClassStage() { return m_stage; }
	const std::shared_ptr<Enemy>&GetClassEnemy() { return m_enemy; }
	const std::list<std::shared_ptr<Item>>&GetClassItemList(){ return m_item_list; }
	const std::list<std::shared_ptr<Item>>&GetClassTutorialItemList() { return m_item_tutorial_list; }
	const std::list<std::shared_ptr<StageWall>>&GetClassStageWall() { return m_stagewall_list; }
	const std::list<std::shared_ptr<StageWall>>&GetClassStageTutorial() { return m_stage_tutorial_list; }
	const std::shared_ptr<BackGroundStage>&GetClassBackGroundStage() { return m_background; }
	const std::shared_ptr<Inventory>&GetClassInventory() { return m_inventory; }
	const std::shared_ptr<Message>&GetClassMessage() { return m_message; }
	
private:
	//�`���[�g���A���}�b�v��csv�n���h��
	std::vector<std::vector<int>> m_tutorial_csv;

	//------------��������N���X�̃|�C���^------------------------//
	//�C���^�[�t�F�[�X�I�����������f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//�I�u�W�F�N�g�̃��X�g
	std::list<std::shared_ptr<GameObject>>m_object_list;
	//�I�u�W�F�N�g�`���[�g���A���̃��X�g
	std::list<std::shared_ptr<GameObject>>m_object_tutorial_list;
	//�J�����N���X�̃X�}�[�g�|�C���^
	std::shared_ptr<GameCamera>m_gamecamera = nullptr;
	//�v���C���[�̃X�}�[�g�|�C���^
	std::shared_ptr<Player>m_player = nullptr;
	//Enemy�̃X�}�[�g�|�C���^
	std::shared_ptr<Enemy>m_enemy = nullptr;
	//Item�̃X�}�[�g�|�C���^
	std::list<std::shared_ptr<Item>>m_item_list;
	//�`���[�g���A���ł̂ݎg��Item�̃��X�g
	std::list<std::shared_ptr<Item>>m_item_tutorial_list;
	//�X�e�[�W�v�Z�̃N���X
	std::shared_ptr<Stage>m_stage = nullptr;
	//�X�e�[�W�̕ǃN���X���X�g
	std::list<std::shared_ptr<StageWall>>m_stagewall_list;
	std::list<std::shared_ptr<StageWall>>m_stage_tutorial_list;
	//�X�e�[�W�̕`��N���X
	std::shared_ptr<BackGroundStage>m_background = nullptr;
	//�Ɩ��N���X���X�g
	std::list<std::shared_ptr<Fluorescent>>m_fluorescent_list;
	//���͂̃f�[�^�N���X�|�C���^
	std::shared_ptr<Message>m_message = nullptr;
	//�C���x���g���[
	std::shared_ptr<Inventory>m_inventory = nullptr;


};
