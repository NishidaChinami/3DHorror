#include "../dxlib_ext/dxlib_ext.h"
#include"StageParts.h"
#include"../Camera/GameCamera.h"

const tnl::Vector3 StageWall::START_BLOCK_POS = { -300,0,-300 };

StageWall::StageWall(tnl::Vector3 pos, maze::StageState state, std::shared_ptr<dxe::Mesh> cloneBox)
{
	size = { BLOCKSIZE,BLOCKHIGHT,BLOCKSIZE };
	mesh = cloneBox;
	mesh->pos_ = pos;
	state = m_state;
	mesh->setMtrlEmissive({ 0.2,0.2,0.2 });
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
	if (tnl::IsIntersectRayAABB(
		gamecamera->pos_
		, gamecamera->GetRay()
		, tnl::ToMaxAABB(mesh->pos_ + tnl::Vector3(-size.x / 2, size.y / 2, size.z / 2), size)
		, tnl::ToMinAABB(mesh->pos_ + tnl::Vector3(size.x / 2, -size.y / 2, -size.z / 2), size))) {
		if (m_state == maze::StageState::Goal) {
			DrawStringEx(500, 400, -1, "äOÇ÷èoÇÈ");
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
				Goal();
			}
		}
	}

}

void StageWall::Goal() {

}