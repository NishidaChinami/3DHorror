#include "../dxlib_ext/dxlib_ext.h"
#include"StageParts.h"
#include"../Camera/GameCamera.h"
#include"../../Manager/Manager.h"
#include"../../Manager/Mediator.h"
#include"../../Scene/ResultScene.h"

const tnl::Vector3 StageWall::START_BLOCK_POS = { -300,0,-300 };

StageWall::StageWall(tnl::Vector3 pos, maze::StageState state, std::shared_ptr<dxe::Mesh> cloneBox, const std::shared_ptr<Mediator>mediator)
{
	size = { BLOCKSIZE,BLOCKHIGHT,BLOCKSIZE };
	mesh = cloneBox;
	mesh->pos_ = pos;
	m_state = state;
	mesh->setMtrlEmissive({ 0.2,0.2,0.2 });
	if (mediator)m_mediator = mediator;
}

StageWall::StageWall(tnl::Vector3 pos, std::shared_ptr<dxe::Mesh> cloneBox)
{
	size = { BLOCKSIZE,BLOCKHIGHT,BLOCKSIZE };
	mesh = cloneBox;
	mesh->pos_ = pos;
	mesh->setMtrlEmissive({ 0.2,0.2,0.2 });
}
void StageWall::Draw(std::shared_ptr<GameCamera>gamecamera) {
	mesh->render(gamecamera);
	
	if (m_state == maze::StageState::Goal) {
		if (tnl::IsIntersectRayAABB(
			gamecamera->pos_
			, gamecamera->GetRay()
			, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
			, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2), size))) {
				DrawStringEx(500, 400, -1, "外へ出る");
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
					Goal();
				}
		}
	}

}

void StageWall::Goal() {
	if (m_mediator->MGetItemFloopy() == 5) {
		auto manager = GameManager::GetInstance();
		manager->can_clear = true;
		manager->ChangeScene(std::make_shared<ResultScene>());
	}
	else {
		DrawStringEx(500, 300, -1, "フロッピーディスクが足りない");
	}
}