#include "../dxlib_ext/dxlib_ext.h"
#include"Item.h"
#include"../Camera/GameCamera.h"
#include"../Mylibrary/Conversion.h"
#include"../../Manager/Mediator.h"

Item::Item(tnl::Vector3 pos, int articletype)
{
	size = { 40,60,5 };
	mesh = dxe::Mesh::CreateBoxMV
	(size,
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//横は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//横は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//上は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//下は白地
	dxe::Texture::CreateFromFile("graphics/Paper.png"),
	dxe::Texture::CreateFromFile("graphics/Paper.png"));
	
	mesh->pos_ = pos;
	mesh->setMtrlEmissive({ 0.5,0.5,0.5 });
	m_itemtype = ItemType::Article;
	m_article_type = articletype;
}
Item::Item(const tnl::Vector3 &pos, int type, const std::shared_ptr<Mediator>mediator) {
	
	m_mediator = mediator;
	m_itemtype = static_cast<ItemType>(type);
	item_detail_csv = tnl::LoadCsv("csv/Item.csv");

	for (int i = 1; i < item_detail_csv.size(); i++) {
		if (type == item_detail_csv[i][0].getInt()) {
			size = { item_detail_csv[i][1].getFloat() };
			m_item_hdl = LoadGraph(item_detail_csv[i][2].getString().c_str());
			m_item_model_hdl = MV1LoadModel(item_detail_csv[i][3].getString().c_str());
			m_item_texture_hdl = LoadGraph(item_detail_csv[i][4].getString().c_str());
			m_item_explanation = item_detail_csv[i][5].getString().c_str();
			m_scale = item_detail_csv[i][6].getFloat();
		}
	}
	mesh = dxe::Mesh::CreateSphereMV(size.x);
	mesh->pos_ = pos;
	MV1SetTextureGraphHandle(m_item_model_hdl, 0, m_item_texture_hdl, FALSE);
	MV1SetScale(m_item_model_hdl, VGet(m_scale, m_scale, m_scale));
	MV1SetMaterialEmiColor(m_item_model_hdl, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));//Difcolor
	MV1SetPosition(m_item_model_hdl, cf::ConvertToV3(mesh->pos_));
}
Item::~Item()
{
}


void Item::Update(float delta_time) {

}

void Item::PassInventory() {
	//そのアイテムが有効かどうか
	if (m_isvalid) {
		//記事だったらとれない
		if (m_itemtype == ItemType::Article) {
			ArticalEvent();
			
		}
		//インベントリーに入れられるか
		else if (m_mediator->MSetPassInventory(shared_from_this())) {
			m_isvalid = false;
			if(m_itemtype == ItemType::Floppy)keycount++;
			if (m_itemtype == ItemType::FrashLight)m_mediator->MSetLightParam(true);
		}
	}
	
	//音を鳴らす
}

void Item::Draw(std::shared_ptr<GameCamera>gamecamera) {
	if (m_isvalid) {
		if(m_itemtype == ItemType::Article)mesh->render(gamecamera);
		MV1DrawModel(m_item_model_hdl);
	}
	if (tnl::IsIntersectRayAABB(
		gamecamera->pos_
		, gamecamera->GetRay()
		, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
		, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2),size))) {
		DrawStringEx(500, 400, -1, "E で取る");
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
			PassInventory();
		}
	}
}

void Item::ArticalEvent() {
	//UIクラスを呼び出す
	//カウントする
	//カウントに応じた文字を呼び出す
	
	m_mediator->MSetMessage(m_article_type, m_readarticle);
}

