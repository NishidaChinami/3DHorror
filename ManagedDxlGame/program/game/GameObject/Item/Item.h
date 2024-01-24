#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"../GameObject.h"
#include"../../GameObject/Stage/Stage.h"
#include"../Stage/StageParts.h"

class GameCamera;
class Inventory;
class Mediator;

class Item: public GameObject, public std::enable_shared_from_this<Item>
{
public:
	enum class ItemType {
		Floppy,
		FrashLight,
		Battery,
		Pills,
		Medikit,
		Article
	};
	Item() {};
	Item(tnl::Vector3 pos,int articletype);
	Item(const tnl::Vector3 &pos,int type, const std::shared_ptr<Mediator>mediator);
	~Item();
	void Update(float delta_time)override;
	void PassInventory();
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	void ArticalEvent();

	tnl::Vector3 GetPos()const { return mesh->pos_; }
	tnl::Vector2i GetGridPos() const { return cf::GridPos(mesh->pos_, StageWall::START_BLOCK_POS, StageWall::BLOCKSIZE); }

	ItemType GetType() const { return m_itemtype; }
	bool GetIsValid() { return m_isvalid; }
	std::string GetExplanation() { return m_item_explanation; }
	int GetUIHdl() { return m_item_hdl; }
	bool GetItem() { return m_getitem; }

	int GetfloopyCount() { return m_floppy_count; }

private:
	//���̃A�C�e����
	ItemType m_itemtype = ItemType::Floppy;
	//�A�C�e���̕`��̃u�[��
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

	//�v���b�s�[���W�߂���
	int m_floppy_count = 0;

	//UI�ւ̒ʒm�p�t���O
	//item�������Ă��邩�ǂ���
	bool m_getitem = false;
	//�L�������ł��邩�ǂ���
	bool m_readarticle = false;

	std::vector<std::vector<tnl::CsvCell>>item_detail_csv;

	std::shared_ptr<Mediator>m_mediator = nullptr;

};

