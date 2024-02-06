#include "../dxlib_ext/dxlib_ext.h"
#include"GameParticle.h"
#include"../../GameObject/Camera/GameCamera.h"

GameParticle::GameParticle()
{
    //パーティクルのファイルを読み込む
    //雨
    m_ptcl_list.emplace_back(std::make_shared<dxe::Particle>("particle/preset/rain.bin"));
    //土の映る雨の模様
    m_ptcl_list.emplace_back(std::make_shared<dxe::Particle>("particle/preset/rain_ground.bin"));

}

GameParticle::~GameParticle()
{
    for (auto ptcl : m_ptcl_list) {
        ptcl.reset();
    }
}
//------------------------------------------------------------------------------------------------------------
//描画処理
void GameParticle::Draw(std::shared_ptr<GameCamera> gamecamera)
{
    //パーティクルの描画開始
    dxe::DirectXRenderBegin();

    // パーティクル の描画
    for (auto ptcl : m_ptcl_list) {
        ptcl->render(gamecamera);
    }
    // パーティクルの描画終了
    dxe::DirectXRenderEnd();
}
