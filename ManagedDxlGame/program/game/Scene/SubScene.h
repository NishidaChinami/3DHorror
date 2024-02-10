#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"
class Inventory;
class Message;
class Factory;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//�T�u�V�[���N���X
// �^�C�g����v���C��ʂ̃N���X�̎q�N���X�Ƃ��ċ@�\
// �C���x���g���[��`���[�g���A���̐����Ȃ�UI�̕\����S��
//-------------------------------------------------------------------------------------------------//

class SubScene : public BaseScene
{
public:
	SubScene() {};
	//�v���C��`���[�g���A���Ŏg���I�u�W�F�N�g�̏�������Factory�N���X��Mediator�N���X�������Ɏ���
	SubScene(std::shared_ptr<Factory>factory, std::shared_ptr<Mediator>mediator);
	~SubScene();
	//�V�[���̍X�V
	void Update(float delta_time)override;
	//�V�[���̕`��֐�
	void Draw()override;

	//�`���[�g���A���ŕ\�������������
	struct TutorialDate
	{
		std::string s_mess; //�`���[�g���A���̐�����
		eKeys s_key;        //���͑҂�����L�[
		bool s_light_flug;  //�����d���������Ă��邩�ǂ���
	};
	//�`���[�g���A���\���̃R���[�`��
	TNL_CO_SEQUENCE(SubScene, &SubScene::seqIdle);

	//--------------------------Getter/Setter------------------------//
	TNL_PROPERTY(bool, BoolInventory, m_active_inventory);
	TNL_PROPERTY(bool, BoolEvent, m_active_event);
	TNL_PROPERTY(bool, BoolTutorial, m_active_tutorial);

private:
	//�V�[���J�ڗp�̃e���v���[�g
	tnl::Sequence<SubScene> sequence_ = tnl::Sequence<SubScene>(this, &SubScene::seqIdle);
	//���ʉ�ʂ܂��̓X�^�[�g��ʂɖ߂�
	bool seqIdle(float delta_time);
	bool seqTutorialUI(float delta_time);
	bool seqEventUI(float delta_time);
	bool seqInventoryUI(float delta_time);

	//�eUI�̕\���̃t���O
	bool m_active_inventory = false;
	bool m_active_event = false;
	bool m_active_tutorial = true;

	//�t�F�[�h�A�E�g�p�ϐ�
	int m_alpha = 0;
	float m_time_count = 0;

	//�`���[�g���A���ŕ\�����镶���̕ϐ�
	std::string m_tutorial_message;
	//�`���[�g���A���f�[�^��ۑ�����x�N�^�[
	std::vector<TutorialDate>m_tutorial_date;

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Factory>m_factory;
	std::shared_ptr<Mediator>m_mediator;
	//----------------------�萔------------------------//
	//�C�x���gUI�������̔w�i��ʂ̃T�C�Y
	const float EVENTUI_WIGHT = 800;
	const float EVENTUI_HEIGHT = 600;
	//�e�����̍��W
	const tnl::Vector3 TUTORIAL_MESSEAGE = { 640,500,0 };
	const tnl::Vector3 DASHGAUGE_POS = { 640,620,0 };
	//�̗̓Q�[�W�̍���
	const float GAUGE_HEIGHT = 5;
	//�����̃T�C�Y
	const int TUTORIAL_FONT = 20;
	const int EVENT_FONT = 18;
	const int INVENTORY_FONT = 20;

};

