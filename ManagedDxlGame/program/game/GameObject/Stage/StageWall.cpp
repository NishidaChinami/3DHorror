#include "../dxlib_ext/dxlib_ext.h"
//-------------------Manager file------------------------//
#include"../../Manager/Manager.h"
#include"../../Manager/Mediator.h"
//-------------------Scene file------------------------//
#include"../../Scene/ResultScene.h"
//-------------------GameObject file------------------------//
#include"StageWall.h"
#include"../Camera/GameCamera.h"

const tnl::Vector3 StageWall::START_BLOCK_POS = { -300,0,-300 };

StageWall::StageWall(const tnl::Vector3 &pos, maze::StageState state,const std::shared_ptr<Mediator>&mediator)
{
	size = { BLOCKSIZE,BLOCKHEIGHT,BLOCKSIZE };
	mesh = dxe::Mesh::CreateCubeMV(30);
	mesh->pos_ = pos;
	m_state = state;
	mesh->setMtrlEmissive({ 0.2,0.2,0.2 });
	if (mediator)m_mediator = mediator;
}

StageWall::StageWall(const tnl::Vector3 &pos)
{
	size = { BLOCKSIZE,BLOCKHEIGHT,BLOCKSIZE };
	mesh = dxe::Mesh::CreateCubeMV(30);
	mesh->pos_ = pos;
}
//------------------------------------------------------------------------------------------------------------
//�`�揈��
void StageWall::Draw(std::shared_ptr<GameCamera>gamecamera) {
	//�X�e�[�g���S�[���ł���ꍇ
	if (m_state == maze::StageState::Goal) {
		if (!tnl::IsIntersectSphere(mesh->pos_, RANGE, m_mediator->MGetPlayerPos(), m_mediator->MGetPlayerSize().x))return;
		//�v���C���[�̉�ʒ�����Ray�ƃS�[���̓����蔻����Ƃ�
		if (tnl::IsIntersectRayAABB(
			gamecamera->pos_
			, gamecamera->getRay()
			, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
			, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2), size))) {
			//�t���b�s�[�f�B�X�N�����ׂĎ���Ă�����S�[���ł���
			if (m_mediator->MGetItemFloopy()) {
				DrawStringEx(MESS_POS.x, MESS_POS.y, -1, "E �O�֏o��");
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
					Goal();
				}
			}
			//�����łȂ��ꍇ�ȉ��̕�����\��
			else DrawStringEx(MESS_POS.x, MESS_POS.y, -1, "�t���b�s�[�f�B�X�N������Ȃ�");
				
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//�S�[���������̃V�[���؂�ւ����ĂԊ֐�
void StageWall::Goal() {
		auto manager = GameManager::GetInstance();
		manager->can_clear = true;
		manager->ChangeScene(std::make_shared<ResultScene>());
}

