#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/// <summary>
/// Object�N���X�̃C���X�^���X�����N���X
/// </summary>

class Mediator;
class GameObject;
class Player;
class GameCamera;
class Stage;
class StageWall;
class Enemy;
class Item;
class BackGroudStage;
class Sound;
class Fluorescent;
class Inventory;
class Message;

class Factory
{
public:
	Factory();
	~Factory();
	void SetMediator();
	//void Update() {};
	void CreatMesh();
	void CreatMainGame();
	void CreatTutorial();

	void AddMainObject();
	void AddTutorialObject();


	std::list<std::shared_ptr<GameObject>> GetClassObj() { return object; }
	std::list<std::shared_ptr<GameObject>> GetClassObj_Tutorial() { return object_tutorial; }


	std::shared_ptr<GameCamera>GetClassCamera() { return gamecamera; }
	std::shared_ptr<Mediator>GetClassMediator() { return mediator; }
	std::shared_ptr<Player>GetClassPlayer() { return player; }
	std::shared_ptr<Stage>GetClassStage() { return stage; }
	std::shared_ptr<Enemy>GetClassEnemy() { return enemy; }
	std::list<std::shared_ptr<Item>>GetClassItemList(){ return item; }

	std::list<std::shared_ptr<StageWall>>GetClassStageWall() { return stagewall; }
	std::list<std::shared_ptr<StageWall>>GetClassStageTutorial() { return tutorialstage; }
	std::list<std::shared_ptr<BackGroudStage>>GetClassBackGroudStage() { return backgroud; }
	std::list<std::shared_ptr<BackGroudStage>>GetClassSoilGroudStage() { return soilgroud; }

	std::shared_ptr<Sound>GetClassSound() { return sound; }
	//std::list<std::shared_ptr<Fluorescent>>GetClassLightList() { return fluorescent; }
	std::shared_ptr<Inventory>GetClassInventory() { return inventory; }
	std::shared_ptr<Message>GetClassMessage() { return message; }
	
private:
	//�C���^�[�t�F�[�X�I�����������f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator>mediator = nullptr;
	//�I�u�W�F�N�g�̃��X�g�|�C���^
	std::list<std::shared_ptr<GameObject>>object;
	std::list<std::shared_ptr<GameObject>>object_tutorial;

	//�J�����N���X�̃X�}�[�g�|�C���^
	std::shared_ptr<GameCamera>gamecamera = nullptr;
	//�v���C���[�̃X�}�[�g�|�C���^
	std::shared_ptr<Player>player = nullptr;
	//Enemy�̃X�}�[�g�|�C���^
	std::shared_ptr<Enemy>enemy = nullptr;
	//Item�̃X�}�[�g�|�C���^
	std::list<std::shared_ptr<Item>>item;
	std::list<std::shared_ptr<Item>>item_tutorial;

	//�T�E���h�N���X
	std::shared_ptr<Sound>sound;
	//�X�e�[�W�v�Z�̃N���X
	std::shared_ptr<Stage>stage = nullptr;
	//�X�e�[�W�̕ǃN���X���X�g
	std::list<std::shared_ptr<StageWall>>stagewall;
	std::list<std::shared_ptr<StageWall>>tutorialstage;
	//�X�e�[�W�̓V��Ə��̃��X�g
	std::list<std::shared_ptr<BackGroudStage>>backgroud;
	std::list<std::shared_ptr<BackGroudStage>>soilgroud;
	
	//�Ɩ��N���X���X�g
	std::list<std::shared_ptr<Fluorescent>>fluorescent;
	//���͂̃f�[�^�N���X�|�C���^
	std::shared_ptr<Message>message = nullptr;
	//�C���x���g���[
	std::shared_ptr<Inventory>inventory = nullptr;
	

	//�R�s�[���b�V��
	std::shared_ptr<dxe::Mesh>groudmesh = nullptr;
	std::vector<std::shared_ptr<dxe::Mesh>>copy_groud_mesh;

	std::shared_ptr<dxe::Mesh>wallmesh = nullptr;
	std::vector<std::shared_ptr<dxe::Mesh>>copy_mesh;

	std::shared_ptr<dxe::Mesh>gaolmesh = nullptr;

	std::shared_ptr<dxe::Mesh>soilmesh = nullptr;
	std::shared_ptr<dxe::Mesh>tutorialmesh = nullptr;
	

	//���b�V���̃C���f�b�N�X
	int mesh_index = 0;

	//�`���[�g���A���}�b�v��csv�n���h��
	std::vector<std::vector<int>> tutorial_csv;

};
