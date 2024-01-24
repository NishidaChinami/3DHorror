#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/maze.h"


class Player;
class StageWall;
class GameCamera;
class Stage;
class Enemy;
class Item;
class Flashlight;
class MainUI;
class Inventory;
class Message;

class Mediator
{
public:
	Mediator() {};
	~Mediator() {};

	//player��Getter��Setter
	tnl::Vector3 MGetPlayerPos();
	tnl::Quaternion MGetPlayerRot();
	tnl::Vector3 MGetPlayerSize();
	float MGetPlayerSpeed();
	float MGetPlayerStamina();

	//Enemy��Getter��Setter
	tnl::Vector3 MGetEnemyPos();
	tnl::Vector3 MGetEnemySize();
	bool MGetChaseState();

	//stage��stagestate�Q�����z��̎擾
	maze::StageState MGetStageState(int r, int c);
	//Item�̈ʒu���擾
	std::vector<tnl::Vector2i> MGetItemPos();
	//�t���b�s�[�f�B�X�N�̐�
	int MGetItemFloopy();
	

	//MainUI�ɒʒm��^����
	bool MSetMessage(int title, bool notify = false);
	//Inventory���̎擾
	bool MSetPassInventory(const std::shared_ptr<Item>& item);
	

	void SetPlayerClass(const std::shared_ptr<Player>&player) { m_player = player; }
	void SetStageClass(const std::shared_ptr<Stage>&stage) { m_stage = stage; }
	void SetStageWallClass(const std::list<std::shared_ptr<StageWall>>& stagewall) { m_stagewall_list= stagewall; }
	void SetEnemyClass(std::shared_ptr<Enemy>&enemy) { m_enemy = enemy; }
	void SetItemClass(const std::list<std::shared_ptr<Item>>& item) { m_item_list = item; }
	void SetMessageClass(const std::shared_ptr<Message>& message) { m_message = message; }
	void SetInventoryClass(const std::shared_ptr<Inventory>& inventory) { m_inventory = inventory; }
	
	void MSetLightParam(bool light) { m_getlight = light; }
	bool MGetLightParam() { return m_getlight; }
private:
	std::shared_ptr<Player>m_player = nullptr;
	std::list<std::shared_ptr<StageWall>>m_stagewall_list;
	std::shared_ptr<GameCamera>m_camera = nullptr;
	std::shared_ptr<Stage>m_stage = nullptr;
	std::shared_ptr<Enemy>m_enemy = nullptr;
	std::list<std::shared_ptr<Item>>m_item_list;
	//std::shared_ptr<Flashlight>m_light = nullptr;

	std::shared_ptr<Message>m_message = nullptr;
	std::shared_ptr<Inventory>m_inventory = nullptr;

	//���C�g���Q�b�g�������ǂ���
	bool m_getlight = false;


};
