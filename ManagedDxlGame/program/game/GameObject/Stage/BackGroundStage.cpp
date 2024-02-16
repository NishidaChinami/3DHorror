#include "../dxlib_ext/dxlib_ext.h"
//-------------------Manager file------------------------//
#include"../../Manager/Mediator.h"
//-------------------GameObject file------------------------//
#include"BackGroundStage.h"
#include"Stage.h"
#include"StageWall.h"
#include"../Camera/GameCamera.h"

BackGroundStage::BackGroundStage(const std::shared_ptr<Stage>& stage, const std::shared_ptr<Mediator>& mediator)
{
	//参照を受け取る
	m_stage = stage;
	m_mediator = mediator;
	//ポリゴンタイプとテクスチャーを保存するcsv
	m_mesh_csv = tnl::LoadCsv("csv/mesh.csv");
	//オリジナルメッシュの生成
	for (int i = 1; i < m_mesh_csv.size(); i++) {
		std::shared_ptr<dxe::Mesh>stagemesh;
		tnl::Vector3 mesh_size = { m_mesh_csv[i][2].getFloat(),m_mesh_csv[i][3].getFloat(),m_mesh_csv[i][4].getFloat() };
		//メインステージの場合
		if (0 == m_mesh_csv[i][0].getInt()) {
			//Boxメッシュ場合
			if (0 == m_mesh_csv[i][0].getInt()) {
				stagemesh = dxe::Mesh::CreateBoxMV(mesh_size,
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()), 20, 20);
			}
			//Planeメッシュの場合
			else {
				stagemesh = dxe::Mesh::CreatePlaneMV(mesh_size);
				stagemesh->setTexture(dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()));
			}
			m_main_original_mesh.emplace_back(stagemesh);
		}
		//チュートリアルステージの場合
		else {
			//Boxメッシュ場合
			if (0 == m_mesh_csv[i][1].getInt()) {
				stagemesh = dxe::Mesh::CreateBoxMV(mesh_size,
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()),
					dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()), 20, 20);
			}
			//Planeメッシュの場合
			else {
				stagemesh = dxe::Mesh::CreatePlaneMV(mesh_size);
				stagemesh->setTexture(dxe::Texture::CreateFromFile(m_mesh_csv[i][5].getString().c_str()));

			}
			m_tutorial_original_mesh.emplace_back(stagemesh);
		}
		//メッシュの端がギザギザになるのを防ぐ
		stagemesh->setCullingMode(DX_CULLING_RIGHT);
	}
	//コピーメッシュ作成
	MeshCreate();
	//スカイボックスの生成と初期設定
	m_skybox = dxe::Mesh::CreateCubeMV(30000, 20, 20);
	m_skybox->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_c.png"));
	m_skybox->loadMaterial("material.bin");
	m_skybox->setMtrlEmissive(m_skybox_emmisive);
	
}

BackGroundStage::~BackGroundStage()
{
	
}

//------------------------------------------------------------------------------------------------------------
//オリジナルメッシュからコピーメッシュして壁のメッシュを生成する関数
void BackGroundStage::MeshCreate()
{
	//地面と天井
	for (int row = -1; row < 4; row++) {
		for (int col = -1; col < 4; col++) {
			tnl::Vector3 groudpos;
			Shared<dxe::Mesh>copy_mesh_a = nullptr;
			Shared<dxe::Mesh>copy_mesh_b = nullptr;
		//座標を決める
			groudpos = { 0.0f + BackGroundStage::SIZE * col,StageWall::BLOCKHEIGHT,0.0f+BackGroundStage::SIZE * row };
		
			//クローンの作成
			copy_mesh_a = m_main_original_mesh[0]->createClone();
			copy_mesh_b = m_main_original_mesh[0]->createClone();
			copy_mesh_a->pos_ = groudpos;
			copy_mesh_b->pos_ = { groudpos.x, 0, groudpos.z };
			copy_mesh_a->rot_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-90));
			copy_mesh_b->rot_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-90));
			//メインステージのメッシュベクターに入れる
			m_main_mesh_vector.emplace_back(copy_mesh_a);
			m_main_mesh_vector.emplace_back(copy_mesh_b);

		}
	}
	//メインステージのBoxメッシュの座標を決定
	for (int r = 0; r < Stage::STAGE_ROW; r++) {
		for (int c = 0; c < Stage::STAGE_COL; c++) {
			tnl::Vector3 pos = { -300.0f + c * StageWall::BLOCKSIZE, StageWall::BLOCKHEIGHT/ 2 ,-300.0f + r * StageWall::BLOCKSIZE };
			Shared<dxe::Mesh>copy_mesh = nullptr;
			//壁
			if (m_stage->getStgaeState(r, c) == maze::StageState::Wall)
			{
				copy_mesh = m_main_original_mesh[1]->createClone();
				copy_mesh->pos_ = pos;
				//メインステージのメッシュベクターへ入れる
				m_main_mesh_vector.emplace_back(copy_mesh);
			}
			//ゴール
			else if (m_stage->getStgaeState(r, c) == maze::StageState::Goal) {
				copy_mesh = m_main_original_mesh[2]->createClone();
				copy_mesh->pos_ = pos;
				//メインステージのメッシュベクターへ入れる
				m_main_mesh_vector.emplace_back(copy_mesh);
			}
		}
	}

	//チュートリアルステージのマップを読み込み座標を決定
	m_tutorial_csv = tnl::LoadCsv<int>("csv/TutorialStage.csv");
	for (int i = 0; i < m_tutorial_csv.size(); i++) {
		for (int k = 0; k < m_tutorial_csv[i].size(); k++) {
			Shared<dxe::Mesh>copy_mesh = nullptr;
			tnl::Vector3 pos= { StageWall::START_BLOCK_POS.x + k * StageWall::BLOCKSIZE,SIZE / 2,StageWall::START_BLOCK_POS.z + i * StageWall::BLOCKSIZE };
			
			if (m_tutorial_csv[i][k] == -1)continue;
			//床
			if (m_tutorial_csv[i][k] == 0) {
				copy_mesh = m_tutorial_original_mesh[0]->createClone();
				copy_mesh->pos_ = { pos.x,0,pos.z };
				copy_mesh->rot_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
			}
			//壁
			else if (m_tutorial_csv[i][k] == 1) {
				copy_mesh = m_tutorial_original_mesh[1]->createClone();
				copy_mesh->pos_ = pos;
			}
			//シャッター
			else if (m_tutorial_csv[i][k] == 2) {
				copy_mesh = m_tutorial_original_mesh[2]->createClone();
				copy_mesh->pos_ = pos;
			}
			//チュートリアルメッシュベクターへ入れる
			m_tutorial_mesh_vector.emplace_back(copy_mesh);
		}
	}

	//チュートリアルの外壁の背景の座標と回転の設定
	m_tutorial_original_mesh[3]->pos_ = {StageWall::START_BLOCK_POS.x + StageWall::BLOCKSIZE/2,SIZE / 2,
										StageWall::START_BLOCK_POS.z + m_tutorial_csv.size() / 2 * StageWall::BLOCKSIZE };
	m_tutorial_original_mesh[3]->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-90));
	m_tutorial_original_mesh[4]->pos_ = { StageWall::START_BLOCK_POS.x + m_tutorial_csv.size() / 2 * StageWall::BLOCKSIZE ,SIZE / 2,
										StageWall::START_BLOCK_POS.z + (m_tutorial_csv.size() - 1) * StageWall::BLOCKSIZE - StageWall::BLOCKSIZE / 2 };
	m_tutorial_original_mesh[5]->pos_ = {StageWall::START_BLOCK_POS.x + (m_tutorial_csv.size()-1) *StageWall::BLOCKSIZE - StageWall::BLOCKSIZE / 2,SIZE / 2,
										StageWall::START_BLOCK_POS.z + m_tutorial_csv.size() / 2 * StageWall::BLOCKSIZE },
	m_tutorial_original_mesh[5]->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90));
	m_tutorial_original_mesh[6]->pos_ = { StageWall::START_BLOCK_POS.x + m_tutorial_csv.size() / 2 * StageWall::BLOCKSIZE,SIZE / 2,
										StageWall::START_BLOCK_POS.z + StageWall::BLOCKSIZE / 2};
	m_tutorial_original_mesh[6]->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(180));
	//チュートリアルメッシュベクターに入れる
	m_tutorial_mesh_vector.emplace_back(m_tutorial_original_mesh[3]);
	m_tutorial_mesh_vector.emplace_back(m_tutorial_original_mesh[4]);
	m_tutorial_mesh_vector.emplace_back(m_tutorial_original_mesh[5]);
	m_tutorial_mesh_vector.emplace_back(m_tutorial_original_mesh[6]);

}
//------------------------------------------------------------------------------------------------------------
//メインステージの描画
void BackGroundStage::MainStageDraw(std::shared_ptr<GameCamera> gamecamera)
{
	for (auto mesh : m_main_mesh_vector) {
		mesh->setMtrlEmissive({ 0.1f,0.1f,0.1f });
		//チェイス状態の時壁の自己発光を赤に変更
		if(m_mediator->MGetChaseState())mesh->setMtrlEmissive({ 1.0f,0.0f,0.0f });
		mesh->render(gamecamera);
	}
}
//------------------------------------------------------------------------------------------------------------
//チュートリアルステージの描画
void BackGroundStage::TutorialStageDraw(std::shared_ptr<GameCamera> gamecamera)
{
	//スカイボックスの描画
	m_skybox->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.01f));
	m_skybox->render(gamecamera);
	//ステージの描画
	for (int i = 0; i < m_tutorial_mesh_vector.size(); i++) {
		m_tutorial_mesh_vector[i]->render(gamecamera);
	}
	
}