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
	std::list<std::shared_ptr<GameObject>> GetClassObj() { return object; }
	std::list<std::shared_ptr<GameObject>> GetClassObj_Tutorial() { return object_tutorial; }
	std::shared_ptr<GameCamera>GetClassCamera() { return gamecamera; }
	std::shared_ptr<Mediator>GetClassMediator() { return mediator; }
	std::shared_ptr<Player>GetClassPlayer() { return player; }
	std::shared_ptr<Stage>GetClassStage() { return stage; }
	std::shared_ptr<Enemy>GetClassEnemy() { return enemy; }
	std::list<std::shared_ptr<Item>>GetClassItemList(){ return item; }
	std::list<std::shared_ptr<Item>>GetClassTutorialItemList() { return item_tutorial; }
	std::list<std::shared_ptr<StageWall>>GetClassStageWall() { return stagewall; }
	std::list<std::shared_ptr<StageWall>>GetClassStageTutorial() { return tutorialstage; }
	std::shared_ptr<BackGroundStage>GetClassBackGroundStage() { return background; }
	std::shared_ptr<Inventory>GetClassInventory() { return inventory; }
	std::shared_ptr<Message>GetClassMessage() { return message; }
	
private:
	//�`���[�g���A���}�b�v��csv�n���h��
	std::vector<std::vector<int>> tutorial_csv;

	//------------��������N���X�̃|�C���^------------------------//
	//�C���^�[�t�F�[�X�I�����������f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator>mediator = nullptr;
	//�I�u�W�F�N�g�̃��X�g
	std::list<std::shared_ptr<GameObject>>object;
	//�I�u�W�F�N�g�`���[�g���A���̃��X�g
	std::list<std::shared_ptr<GameObject>>object_tutorial;
	//�J�����N���X�̃X�}�[�g�|�C���^
	std::shared_ptr<GameCamera>gamecamera = nullptr;
	//�v���C���[�̃X�}�[�g�|�C���^
	std::shared_ptr<Player>player = nullptr;
	//Enemy�̃X�}�[�g�|�C���^
	std::shared_ptr<Enemy>enemy = nullptr;
	//Item�̃X�}�[�g�|�C���^
	std::list<std::shared_ptr<Item>>item;
	//�`���[�g���A���ł̂ݎg��Item�̃��X�g
	std::list<std::shared_ptr<Item>>item_tutorial;
	//�X�e�[�W�v�Z�̃N���X
	std::shared_ptr<Stage>stage = nullptr;
	//�X�e�[�W�̕ǃN���X���X�g
	std::list<std::shared_ptr<StageWall>>stagewall;
	std::list<std::shared_ptr<StageWall>>tutorialstage;
	//�X�e�[�W�̕`��N���X
	std::shared_ptr<BackGroundStage>background = nullptr;
	//�Ɩ��N���X���X�g
	std::list<std::shared_ptr<Fluorescent>>fluorescent;
	//���͂̃f�[�^�N���X�|�C���^
	std::shared_ptr<Message>message = nullptr;
	//�C���x���g���[
	std::shared_ptr<Inventory>inventory = nullptr;


};
