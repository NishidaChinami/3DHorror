#include "../dxlib_ext/dxlib_ext.h"
//-------------------Manager file------------------------//
#include"Mediator.h"
//-------------------GameObject file------------------------//
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/Stage/StageWall.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/BackGroundStage.h"
//-------------------UI file------------------------//
#include"../UI/Message.h"
#include"../UI/Inventory/Inventory.h"

//--------------------playerのGetterとSetter------------------------------------------------//
tnl::Vector3 Mediator::MGetPlayerPos() {
	auto player = m_player.lock();
	if (player)return player->getPlayerPos();}
tnl::Quaternion Mediator::MGetPlayerRot() {
	auto player = m_player.lock();
	if (player)return player->getPlayerRot();}
tnl::Vector3 Mediator::MGetPlayerSize() {
	auto player = m_player.lock();
	if (player)return player->getPlayerSize();}
float Mediator::MGetPlayerSpeed() {
	auto player = m_player.lock();
	if (player)return player->getPlayerSpeed();}
float Mediator::MGetPlayerStamina() {
	auto player = m_player.lock();
	if (player)return player->getPlayerStamina();}
bool Mediator::MGetPlayerDash(){
	auto player = m_player.lock();
	if (player)return player->getPlayerDash();}

//--------------------EnemyのGetterとSetter------------------------------------------------//
tnl::Vector3 Mediator::MGetEnemyPos() {
	auto enemy = m_enemy.lock();
	if(enemy)return enemy->getEnemyPos();}
tnl::Vector3 Mediator::MGetEnemySize() {
	auto enemy = m_enemy.lock();
	if (enemy)return enemy->getEnemySize();}
bool Mediator::MGetChaseState() {
	auto enemy = m_enemy.lock();
	if (enemy)return enemy->getChaseState();}

//--------------------ステージのGetterとSetter------------------------------------------------//
maze::StageState Mediator::MGetStageState(int r, int c) {
	auto stage = m_stage.lock();
	if (stage)return stage->getStgaeState(r, c);}

//--------------------アイテムのGetterとSetter------------------------------------------------//
std::vector<tnl::Vector2i> Mediator::MGetItemPos() {
	std::vector<tnl::Vector2i> itempos;
	for (auto it : m_item_list) {
		auto item = it.lock();
		if(item)itempos.emplace_back(item->getGridPos());
	}
	return itempos;
}

bool Mediator::MGetItemFloopy()
{
	auto it = m_item_list.begin();
	while (it != m_item_list.end()) {
		auto item = (*it).lock();
		if (item) {
			if (item->getType() == Item::ItemType::Floppy) 
				if (item->getIsValid())return false;
		}
		it++;
	}
	return true;
}

bool Mediator::MGetReadArticle()
{
	auto it = m_item_list.begin();
	while (it != m_item_list.end()) {
		auto item = (*it).lock();
		if(item)if(item->getReadArticle())return true;
		it++;
	}
	auto it_t = m_tutorialitem_list.begin();
	while (it_t != m_tutorialitem_list.end()) {
		auto tutorialitem = (*it_t).lock();
		if(tutorialitem)if (tutorialitem->getReadArticle())return true;
		it_t++;
	}
	return false;
}

void Mediator::MSetReadArticle(bool read)
{
	for (auto it : m_item_list){
		auto item = it.lock();
		if(item)if(item->getReadArticle())item->setReadArticle(read);
	}
	for (auto it_t : m_tutorialitem_list) {
		auto tutorialitem = it_t.lock();
		if(tutorialitem)if (tutorialitem->getReadArticle())tutorialitem->setReadArticle(read);
	}
}

//--------------------メッセージ------------------------------------------------//

void Mediator::MSetMessage(int title) {
	//ストーリーをメッセージの情報と照合して表示するメッセージをセットする関数に伝える
	auto message = m_message.lock();
	if(message)message->ChangeStory(title);
}

int Mediator::MGetTitleType(){
	auto message = m_message.lock();
	if (message)return static_cast<int>(message->getTitleType());}


//--------------------インベントリー------------------------------------------------//

bool Mediator::MSetPassInventory(const std::shared_ptr<Item>& item) {
	auto inventory = m_inventory.lock();
	if(inventory)return inventory->IsCanGetItem(item);}

//--------------------スカイボックスのGetterとSetter------------------------------------------------//

void Mediator::MSetSkyEmissive(tnl::Vector3 param){
	auto background = m_backgroundstage.lock();
	if(background)background->setSkyEmissive(param);}
tnl::Vector3 Mediator::MGetSkyEmissive(){
	auto background = m_backgroundstage.lock();
	if (background)return background->getSkyEmissive();}

