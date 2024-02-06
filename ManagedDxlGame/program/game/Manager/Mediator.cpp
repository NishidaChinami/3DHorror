#include "../dxlib_ext/dxlib_ext.h"
//-------------------Manager file------------------------//
#include"Mediator.h"
//-------------------GameObject file------------------------//
#include"../GameObject/Character/Player/Player.h"
#include"../GameObject/Character/Enemy/Enemy.h"
#include"../GameObject/Camera/GameCamera.h"
#include"../GameObject/Stage/Stage.h"
#include"../GameObject/Stage/StageParts.h"
#include"../GameObject/Item/Item.h"
#include"../GameObject/Stage/BackGroudStage.h"
//-------------------UI file------------------------//
#include"../UI/Message.h"
#include"../UI/Inventory/Inventory.h"

//--------------------player��Getter��Setter------------------------------------------------//
tnl::Vector3 Mediator::MGetPlayerPos() {return m_player->getPlayerPos();}
tnl::Quaternion Mediator::MGetPlayerRot() {return m_player->getPlayerRot();}
tnl::Vector3 Mediator::MGetPlayerSize() {return m_player->getPlayerSize();}
float Mediator::MGetPlayerSpeed() {return m_player->getPlayerSpeed();}
float Mediator::MGetPlayerStamina() {return m_player->getPlayerStamina();}
bool Mediator::MGetPlayerDash(){return m_player->getPlayerDash();}

//--------------------Enemy��Getter��Setter------------------------------------------------//
tnl::Vector3 Mediator::MGetEnemyPos() {return m_enemy->getEnemyPos();}
tnl::Vector3 Mediator::MGetEnemySize() {return m_enemy->getEnemySize();}
bool Mediator::MGetChaseState() {	return m_enemy->getChaseState();}

//--------------------�X�e�[�W��Getter��Setter------------------------------------------------//
maze::StageState Mediator::MGetStageState(int r, int c) {return m_stage->getStgaeState(r, c);}

//--------------------�A�C�e����Getter��Setter------------------------------------------------//
std::vector<tnl::Vector2i> Mediator::MGetItemPos() {
	std::vector<tnl::Vector2i> itempos;
	for (auto it : m_item_list) {
		itempos.emplace_back(it->getGridPos());
	}
	return itempos;
}

bool Mediator::MGetItemFloopy()
{
	auto it = m_item_list.begin();
	while (it != m_item_list.end()) {
		if ((*it)->getType() == Item::ItemType::Floppy) {
			if ((*it)->getIsValid())return false;
		}
		it++;
	}
	return true;
}

bool Mediator::MGetReadArticle()
{
	auto it = m_item_list.begin();
	while (it != m_item_list.end()) {
		if((*it)->getReadArticle())return true;
		it++;
	}
	auto it_t = m_tutorialitem_list.begin();
	while (it_t != m_tutorialitem_list.end()) {
		if ((*it_t)->getReadArticle())return true;
		it_t++;
	}
	return false;
}

void Mediator::MSetReadArticle(bool read)
{
	for (auto it : m_item_list){
		if(it->getReadArticle())it->setReadArticle(read);
	}
	for (auto it_t : m_tutorialitem_list) {
		if (it_t->getReadArticle())it_t->setReadArticle(read);
	}
}

//--------------------���b�Z�[�W------------------------------------------------//

void Mediator::MSetMessage(int title) {
	//�X�g�[���[�����b�Z�[�W�̏��Əƍ����ĕ\�����郁�b�Z�[�W���Z�b�g����֐��ɓ`����
	m_message->ChangeStory(title);
}

int Mediator::MGetTitleType(){return static_cast<int>(m_message->getTitleType());}


//--------------------�C���x���g���[------------------------------------------------//

bool Mediator::MSetPassInventory(const std::shared_ptr<Item>& item) {return m_inventory->IsCanGetItem(item);}

//--------------------�X�J�C�{�b�N�X��Getter��Setter------------------------------------------------//

void Mediator::MSetSkyEmissive(tnl::Vector3 param){m_backgroundstage->setSkyEmissive(param);}
tnl::Vector3 Mediator::MGetSkyEmissive(){return m_backgroundstage->getSkyEmissive();}

