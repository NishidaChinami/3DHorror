#include "../dxlib_ext/dxlib_ext.h"
#include"Mediator.h"
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/Stage/StageParts.h"
#include"../GameObject/Item/Item.h"
#include"../UI/Message.h"
#include"../UI/MainUI.h"
#include"../UI/Inventory/Inventory.h"

//ƒJƒƒ‰‚ÉŽQÆ
tnl::Vector3 Mediator::MGetPlayerPos() {
	return m_player->GetPlayerPos();
}

tnl::Quaternion Mediator::MGetPlayerRot() {
	return m_player->GetPlayerRot();
}

tnl::Vector3 Mediator::MGetPlayerSize() {
	return m_player->GetPlayerSize();
}

float Mediator::MGetPlayerSpeed() {
	return m_player->GetPlayerSpeed();
}

float Mediator::MGetPlayerStamina() {
	return m_player->GetPlayerStamina();
}

//“G
tnl::Vector3 Mediator::MGetEnemyPos() {
	return m_enemy->GetEnemyPos();
}
tnl::Vector3 Mediator::MGetEnemySize() {
	return m_enemy->GetEnemySize();
}
bool Mediator::MGetChaseState() {
	return m_enemy->GetChaseState();
}


maze::StageState Mediator::MGetStageState(int r, int c) {
	return m_stage->GetStgaeState(r, c);
}


std::vector<tnl::Vector2i> Mediator::MGetItemPos() {
	std::vector<tnl::Vector2i> itempos;
	for (auto it : m_item_list) {
		itempos.emplace_back(it->GetGridPos());
	}
	return itempos;
}

bool Mediator::MSetMessage(int title, bool notify) {
	m_message->ChangeStory(title);
	if (notify) {
		notify = false;
		return true;
	}
	else return false;
}

bool Mediator::MSetPassInventory(const std::shared_ptr<Item>& item) {
	return m_inventory->IsCanGetItem(item);
}

