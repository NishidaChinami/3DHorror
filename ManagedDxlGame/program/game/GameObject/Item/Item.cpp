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
	//アイテムのサイズの設定
	size = { 40,60,5 };
	//メッシュを生成
	mesh = dxe::Mesh::CreateBoxMV
	(size,
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//横は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//横は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//上は白地
	dxe::Texture::CreateFromFile("graphics/Paper1.png"),//下は白地
	dxe::Texture::CreateFromFile("graphics/Paper.png"),
	dxe::Texture::CreateFromFile("graphics/Paper.png"));
	//生成する座標を受け取る
	mesh->pos_ = pos;
	mesh->rot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(90));
	m_mediator = mediator;
	//自己発光
	mesh->setMtrlEmissive({ 0.5,0.5,0.5 });
	//アイテムタイプとストーリーの設定
	m_itemtype = ItemType::Article;
	m_article_type = articletype;

}
Item::Item(const tnl::Vector3 &pos, ItemType type, const std::shared_ptr<Mediator>&mediator) {
	//アイテムタイプを受け取る
	m_itemtype = type;
	m_mediator = mediator;
	//csvからアイテムの初期設定を読み込む
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
	//当たり判定用に透明のメッシュを生成
	mesh = dxe::Mesh::CreateSphereMV(size.x);
	//生成座標を受け取る
	mesh->pos_ = {pos.x,10,pos.z};
	//MV1Modelの設定をする
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
//更新処理
void Item::Update(float delta_time) {
	//チュートリアルで手に入れるアイテムをメインゲームに引き継ぐ
	//データだけを受け渡せるようにしたいが、この部分は改善が必要
	if (m_isvalid && !GameManager::GetInstance()->is_tutorial) {
		if (m_itemtype == ItemType::FrashLight) {
			m_mediator->MSetPassInventory(shared_from_this());
			m_mediator->MSetLightParam(true);
			m_isvalid = false;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//インベントリーに情報を渡す
void Item::PassInventory() {
	auto sound = Sound::GetInstance();
	//そのアイテムが有効かどうか
	if (m_isvalid) {
		//記事だったらとれない
		if (m_itemtype == ItemType::Article) {
			sound->Sound2DPlay("ARTICLE", DX_PLAYTYPE_BACK);
			m_mediator->MSetMessage(m_article_type);
			m_readarticle = true;
		}
		//インベントリーに入れられるか
		else if (m_mediator->MSetPassInventory(shared_from_this())) {
			sound->Sound2DPlay("GET", DX_PLAYTYPE_BACK);
			m_isvalid = false;
			if (m_itemtype == ItemType::FrashLight) {
				//懐中電灯を取った
				m_mediator->MSetLightParam(true);
				sound->Sound2DPlay("KARASU", DX_PLAYTYPE_BACK);
				sound->Sound2DPlay("TUTORIAL");
			}
		}
	}

}
//------------------------------------------------------------------------------------------------------------
//描画処理
void Item::Draw(std::shared_ptr<GameCamera>gamecamera) {
	tnl::Vector3 mess_pos = gamecamera->GetScreenPos(mesh->pos_);
	//アイテムが有効の時は描画
	if (m_isvalid) {
		//記事アイテムはBoxのポリゴンを使用しているためmeshから描画
		if (m_itemtype == ItemType::Article)mesh->render(gamecamera);
		//その他アイテムはMV1Modelなので、DxlibのMV1描画用関数で描画
		MV1DrawModel(m_item_model_hdl);
		if (!tnl::IsIntersectSphere(mesh->pos_, ITEM_RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x))return;
		//アイテムが一定範囲内かつ画面中央のRayがアイテムと当たっていたら、
		if (tnl::IsIntersectRayAABB(
			gamecamera->pos_
			, gamecamera->getRay()
			, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
			, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2), size))) {
			DrawStringEx(mess_pos.x + ITEM_MESS_POS.x, mess_pos.y + ITEM_MESS_POS.y, -1, "E で取る");
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) PassInventory();
		}
	}
}


