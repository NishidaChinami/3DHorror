#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../GameObject.h"
#include"../../GameObject/Stage/Stage.h"
#include"../Stage/StageWall.h"

class GameCamera;
class Inventory;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//�A�C�e���N���X
// �E�o�̂��߂ɕK�v�ȃA�C�e����V�i���I�����A�C�e��������
// ������A�C�e���̓C���x���g���[�ɓ`������
//-------------------------------------------------------------------------------------------------//

class Item: public GameObject, public std::enable_shared_from_this<Item>
{
public:
	//Item�̎�ނ�Enum�N���X
	enum class ItemType {
		Floppy,
		FrashLight,
		Battery,
		Pills,
		Medikit,
		Article
	};
	Item() {};

	//�X�g�[���[�����A�C�e���̃R���X�g���N�^
	//��1�����@�������W
	//��2�����@�X�g�[���[�̔ԍ�
	//��3�����@�I�u�W�F�N�g�̎Q�ƃN���X���f�B�G�[�^�[�̃|�C���^
	Item(tnl::Vector3 pos, int articletype, const std::shared_ptr<Mediator>&mediator);
	//MV1Model�����A�C�e���̃R���X�g���N�^
	//��1�����@�������W
	//��2�����@�A�C�e���̎��
	//��3�����@�I�u�W�F�N�g�̎Q�ƃN���X���f�B�G�[�^�[�̃|�C���^
	Item(const tnl::Vector3 &pos, ItemType type, const std::shared_ptr<Mediator>&mediator);
	~Item();
	//�X�V����
	void Update(float delta_time)override;
	//�`�揈��
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;
	//�C���x���g���[�ɂ��܂��邩�̔���ƃA�C�e���̏���`����
	void PassInventory();

	//--------------------------Getter/Setter------------------------//
	const tnl::Vector3 &getPos()const { return mesh->pos_; }
	const tnl::Vector2i &getGridPos() const { return cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE); }
	const ItemType &getType() const { return m_itemtype; }
	bool getIsValid()const { return m_isvalid; }
	const std::string &getExplanation() const{ return m_item_explanation; }
	int getUIHdl() const{ return m_item_hdl; }
	bool getItem() const{ return m_getitem; }

	TNL_PROPERTY(bool, ReadArticle, m_readarticle);
private:
	//���̃A�C�e����
	ItemType m_itemtype = ItemType::Floppy;
	//�A�C�e���̕`��̃t���O
	bool m_isvalid = true;
	//�A�C�e���̐�����
	std::string m_item_explanation;
	//UI�p�̉摜
	int m_item_hdl = 0;
	//�A�C�e����model�n���h��
	int m_item_model_hdl;
	//�A�C�e���̃e�N�X�`���[�n���h��
	int m_item_texture_hdl;
	//model�̃X�P�[��
	float m_scale;
	//�L���̎��
	int m_article_type;
	//�A�C�e���̎擾�\����
	const float ITEM_RANGE = 800;
	//UI�ւ̒ʒm�p�t���O
	//item�������Ă��邩�ǂ���
	bool m_getitem = false;
	//�L�������ł��邩�ǂ���
	bool m_readarticle = false;

	//�A�C�e����UI�摜��model��MV1�t�@�C���A�e�N�X�`���[�Ȃǂ̏����Ǘ�����csv�t�@�C���̃��[�h�p�x�N�^�[
	std::vector<std::vector<tnl::CsvCell>>item_detail_csv;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	//�ق��̃I�u�W�F�N�g�N���X�̎Q�Ɨp�|�C���^
	std::shared_ptr<Mediator>m_mediator = nullptr;

	//----------------------�萔------------------------//
	const tnl::Vector3 ITEM_MESS_POS = { 0,100,0 };

};

