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
const tnl::Vector3 &Mediator::MGetPlayerPos() const{
	auto player = m_player.lock();
	if (player)return player->getPlayerPos();}
const tnl::Quaternion &Mediator::MGetPlayerRot()const {
	auto player = m_player.lock();
	if (player)return player->getPlayerRot();}
const tnl::Vector3 &Mediator::MGetPlayerSize() const{
	auto player = m_player.lock();
	if (player)return player->getPlayerSize();}
float Mediator::MGetPlayerSpeed() const{
	auto player = m_player.lock();
	if (player)return player->getPlayerSpeed();}
float Mediator::MGetPlayerStamina()const {
	auto player = m_player.lock();
	if (player)return player->getPlayerStamina();}
bool Mediator::MGetPlayerDash()const{
	auto player = m_player.lock();
	if (player)return player->getPlayerDash();}

//--------------------EnemyのGetterとSetter------------------------------------------------//
const tnl::Vector3 &Mediator::MGetEnemyPos() const{
	auto enemy = m_enemy.lock();
	if(enemy)return enemy->getEnemyPos();}
const tnl::Vector3 &Mediator::MGetEnemySize()const {
	auto enemy = m_enemy.lock();
	if (enemy)return enemy->getEnemySize();}
bool Mediator::MGetChaseState() const {
	auto enemy = m_enemy.lock();
	if (enemy)return enemy->getChaseState();}

//--------------------ステージのGetterとSetter------------------------------------------------//
const maze::StageState &Mediator::MGetStageState(int r, int c)const {
	auto stage = m_stage.lock();
	if (stage)return stage->getStgaeState(r, c);}

bool Mediator::MGetIntersectStage(const tnl::Vector3& pos, const tnl::Vector3& ray,tnl::Vector3* intersect_point)const
{
	auto st = m_stagewall_list.begin();
	while (st != m_stagewall_list.end()) {
		auto stagewall = (*st).lock();
		tnl::Vector3 aabb_max = { stagewall->mesh->pos_ + tnl::Vector3(-StageWall::BLOCKSIZE / 2,StageWall::BLOCKHEIGHT / 2,StageWall::BLOCKSIZE / 2) };
		tnl::Vector3 aabb_min = { stagewall->mesh->pos_ + tnl::Vector3(StageWall::BLOCKSIZE / 2,-StageWall::BLOCKHEIGHT / 2,-StageWall::BLOCKSIZE / 2) };
		//壁とRayが当たってるかどうか
		if (tnl::IsIntersectRayAABB(pos, ray, aabb_max, aabb_min, m_intersect_stage)) {
			if (m_intersect_stage && intersect_point) {
				//比較する交点よりも短い距離であれば偽を返す
				if ((*intersect_point - pos).length() > (*m_intersect_stage - pos).length())return false;
			}
		}
		st++;
	}
	return true;
}

//--------------------アイテムのGetterとSetter------------------------------------------------//
std::vector<tnl::Vector2i> Mediator::MGetItemPos(){
	std::vector<tnl::Vector2i> itempos;
	for (auto it : m_item_list) {
		auto item = it.lock();
		if(item)itempos.emplace_back(item->getGridPos());
	}
	return itempos;
}

bool Mediator::MGetItemFloopy()const
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

bool Mediator::MGetReadArticle()const
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

int Mediator::MGetTitleType()const{
	auto message = m_message.lock();
	if (message)return static_cast<int>(message->getTitleType());}


//--------------------インベントリー------------------------------------------------//

bool Mediator::MSetPassInventory(const std::shared_ptr<Item>& item) {
	auto inventory = m_inventory.lock();
	if(inventory)return inventory->IsCanGetItem(item);}

//--------------------スカイボックスのGetterとSetter------------------------------------------------//

void Mediator::MSetSkyEmissive(tnl::Vector3 &param){
	auto background = m_backgroundstage.lock();
	if(background)background->setSkyEmissive(param);}
const tnl::Vector3 &Mediator::MGetSkyEmissive()const{
	auto background = m_backgroundstage.lock();
	if (background)return background->getSkyEmissive();}

