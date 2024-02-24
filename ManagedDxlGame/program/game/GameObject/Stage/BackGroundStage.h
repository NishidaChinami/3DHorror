#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class GameCamera;
class Stage;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//ステージの描画クラス
//ステージのメッシュを描画する
// グループメッシュ・インスタンシングメッシュで一括描画したかったが、ロードが重くなってしまったため
// ステージのみ描画クラスが分かれてしまった
//-------------------------------------------------------------------------------------------------//
class BackGroundStage
{
public:
	//ステージの当たり判定クラスとメディエータークラスをコンストラクタの引数に持つ
	BackGroundStage(const std::shared_ptr<Stage>&stage, const std::shared_ptr<Mediator>& mediator);
	~BackGroundStage();

	//オリジナルメッシュからコピーメッシュして壁のメッシュを生成する関数
	void MeshCreate();
	//メインステージの描画
	void MainStageDraw(std::shared_ptr<GameCamera>gamecamera);
	//チュートリアルステージの描画
	void TutorialStageDraw(std::shared_ptr<GameCamera>gamecamera);
	//------------Getter/Setter------------------------//
	const tnl::Vector3 &getSkyEmissive() const{return m_skybox->getMtrlEmissive();}
	void setSkyEmissive(const tnl::Vector3 &param) { m_skybox->setMtrlEmissive({ param.x,param.y,param.z }); }
	const std::vector<Shared<dxe::Mesh>>& getMesh()const { return m_tutorial_mesh_vector; }

	//-----------------静的定数--------------------------------//
	//チュートリアルステージの壁の高さ
	static const int SIZE = 1600;
private:

	//メッシュを保存するベクター
	std::vector<Shared<dxe::Mesh>> m_main_mesh_vector;
	std::vector<Shared<dxe::Mesh>> m_tutorial_mesh_vector;

	//ステージのオリジナルメッシュ
	std::vector<Shared<dxe::Mesh>> m_main_original_mesh;
	std::vector<Shared<dxe::Mesh>> m_tutorial_original_mesh;

	//チュートリアルマップのcsvハンドル
	std::vector<std::vector<int>> m_tutorial_csv;
	//ポリゴンタイプとテクスチャーを保存するcsvのロード用ベクター
	std::vector<std::vector<tnl::CsvCell>> m_mesh_csv;
	//エミッシブカラー
	tnl::Vector3 m_skybox_emmisive = { 0.36,0.42,0.42 };

	//------------他クラスの参照用ポインタ------------------------//
	std::shared_ptr<Stage>m_stage = nullptr;
	std::shared_ptr<Mediator>m_mediator = nullptr;
	//スカイボックスのポインタ
	Shared<dxe::Mesh> m_skybox = nullptr;
};



