#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
//-------------------Manager file------------------------//
#include"../../Manager/Mediator.h"
#include"../../Manager/Manager.h"
//-------------------GameObject file------------------------//
#include"Item.h"
#include"../Camera/GameCamera.h"
//-------------------Effect file------------------------//
#include"../../Effect/Sound/Sound.h"
//-------------------UI file------------------------//
#include"../../UI/OptionParam.h"

Item::Item(tnl::Vector3 pos, int articletype,const std::shared_ptr<Mediator> &mediator)
{
	//�A�C�e���̃T�C�Y�̐ݒ�
	size = { 40,60,5 };
	//���b�V���𐶐�
	mesh = dxe::Mesh::CreateBoxMV
	(size,
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//���͔��n
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//���͔��n
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//��͔��n
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//���͔��n
	dxe::Texture::CreateFromFile("graphics/Paper.png"),
	dxe::Texture::CreateFromFile("graphics/Paper.png"));
	//����������W���󂯎��
	mesh->pos_ = pos;
	mesh->rot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(90));
	m_mediator = mediator;
	//���Ȕ���
	mesh->setMtrlEmissive({ 0.5,0.5,0.5 });
	//�A�C�e���^�C�v�ƃX�g�[���[�̐ݒ�
	m_itemtype = ItemType::Article;
	m_article_type = articletype;

}
Item::Item(const tnl::Vector3 &pos, ItemType type, const std::shared_ptr<Mediator>&mediator) {
	//�A�C�e���^�C�v���󂯎��
	m_itemtype = type;
	m_mediator = mediator;
	//csv����A�C�e���̏����ݒ��ǂݍ���
	item_detail_csv = tnl::LoadCsv("csv/Item.csv");

	for (int i = 1; i < item_detail_csv.size(); i++) {
		if (static_cast<int>(type) == item_detail_csv[i][0].getInt()) {
			size = { item_detail_csv[i][1].getFloat() };
			m_item_hdl = LoadGraph(item_detail_csv[i][2].getString().c_str());
			m_item_model_hdl = MV1LoadModel(item_detail_csv[i][3].getString().c_str());
			m_item_texture_hdl = LoadGraph(item_detail_csv[i][4].getString().c_str());
			m_item_explanation = item_detail_csv[i][5].getString().c_str();
			m_scale = item_detail_csv[i][6].getFloat();
		}
	}
	//�����蔻��p�ɓ����̃��b�V���𐶐�
	mesh = dxe::Mesh::CreateSphereMV(size.x);
	//�������W���󂯎��
	mesh->pos_ = {pos.x,10,pos.z};
	//MV1Model�̐ݒ������
	MV1SetTextureGraphHandle(m_item_model_hdl, 0, m_item_texture_hdl, FALSE);
	MV1SetScale(m_item_model_hdl, VGet(m_scale, m_scale, m_scale));
	MV1SetMaterialEmiColor(m_item_model_hdl, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	MV1SetPosition(m_item_model_hdl, cf::ConvertToV3(mesh->pos_));
}
Item::~Item()
{
	DeleteGraph(m_item_texture_hdl);
	DeleteGraph(m_item_hdl);
	MV1DeleteModel(m_item_model_hdl);
}

//------------------------------------------------------------------------------------------------------------
//�X�V����
void Item::Update(float delta_time) {
	//�`���[�g���A���Ŏ�ɓ����A�C�e�������C���Q�[���Ɉ����p��
	//�f�[�^�������󂯓n����悤�ɂ��������A���̕����͉��P���K�v
	if (m_isvalid && !GameManager::GetInstance()->is_tutorial) {
		if (m_itemtype == ItemType::FrashLight) {
			m_mediator->MSetPassInventory(shared_from_this());
			m_mediator->MSetLightParam(true);
			m_isvalid = false;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//�C���x���g���[�ɏ���n��
void Item::PassInventory() {
	auto sound = Sound::GetInstance();
	//���̃A�C�e�����L�����ǂ���
	if (m_isvalid) {
		//�L����������Ƃ�Ȃ�
		if (m_itemtype == ItemType::Article) {
			sound->Sound2DPlay("ARTICLE", DX_PLAYTYPE_BACK);
			m_mediator->MSetMessage(m_article_type);
			m_readarticle = true;
		}
		//�C���x���g���[�ɓ�����邩
		else if (m_mediator->MSetPassInventory(shared_from_this())) {
			sound->Sound2DPlay("GET", DX_PLAYTYPE_BACK);
			m_isvalid = false;
			if (m_itemtype == ItemType::FrashLight) {
				//�����d���������
				m_mediator->MSetLightParam(true);
				sound->Sound2DPlay("KARASU", DX_PLAYTYPE_BACK);
				sound->Sound2DPlay("TUTORIAL");
			}
		}
	}

}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void Item::Draw(std::shared_ptr<GameCamera>gamecamera) {
	tnl::Vector3 mess_pos = gamecamera->GetScreenPos(mesh->pos_);
	//�A�C�e�����L���̎��͕`��
	if (m_isvalid) {
		//�L���A�C�e����Box�̃|���S�����g�p���Ă��邽��mesh����`��
		if (m_itemtype == ItemType::Article)mesh->render(gamecamera);
		//���̑��A�C�e����MV1Model�Ȃ̂ŁADxlib��MV1�`��p�֐��ŕ`��
		MV1DrawModel(m_item_model_hdl);
		if (!tnl::IsIntersectSphere(mesh->pos_, ITEM_RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x))return;
		//�A�C�e�������͈͓�����ʒ�����Ray���A�C�e���Ɠ������Ă�����A
		if (tnl::IsIntersectRayAABB(
			gamecamera->pos_
			, gamecamera->getRay()
			, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
			, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2), size))) {
			DrawStringEx(mess_pos.x + ITEM_MESS_POS.x, mess_pos.y + ITEM_MESS_POS.y, -1, "E �Ŏ��");
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) PassInventory();
		}
	}
}


