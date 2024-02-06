#include "../dxlib_ext/dxlib_ext.h"
#include"GameParticle.h"
#include"../../GameObject/Camera/GameCamera.h"

GameParticle::GameParticle()
{
    //�p�[�e�B�N���̃t�@�C����ǂݍ���
    //�J
    m_ptcl_list.emplace_back(std::make_shared<dxe::Particle>("particle/preset/rain.bin"));
    //�y�̉f��J�̖͗l
    m_ptcl_list.emplace_back(std::make_shared<dxe::Particle>("particle/preset/rain_ground.bin"));

}

GameParticle::~GameParticle()
{
    for (auto ptcl : m_ptcl_list) {
        ptcl.reset();
    }
}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void GameParticle::Draw(std::shared_ptr<GameCamera> gamecamera)
{
    //�p�[�e�B�N���̕`��J�n
    dxe::DirectXRenderBegin();

    // �p�[�e�B�N�� �̕`��
    for (auto ptcl : m_ptcl_list) {
        ptcl->render(gamecamera);
    }
    // �p�[�e�B�N���̕`��I��
    dxe::DirectXRenderEnd();
}
