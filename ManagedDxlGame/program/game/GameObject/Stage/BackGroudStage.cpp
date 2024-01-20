#include "../dxlib_ext/dxlib_ext.h"
#include"BackGroudStage.h"
#include"StageParts.h"
#include"../Camera/GameCamera.h"

BackGroudStage::BackGroudStage(tnl::Vector3 pos, std::shared_ptr<dxe::Mesh> clonePlane, std::shared_ptr<dxe::Mesh> clonePlane2)
{
	floor = clonePlane;
	ceiling = clonePlane2;
	texture = dxe::Texture::CreateFromFile("graphics/Floor.jpg");
	floor->setTexture(texture);
	ceiling->setTexture(texture);
	floor->pos_ = pos - tnl::Vector3(0, StageWall::BLOCKHIGHT / 2, 0);
	ceiling->pos_ = pos + tnl::Vector3(0,StageWall::BLOCKHIGHT/2,0);
	floor->rot_ = tnl::Quaternion::RotationAxis(tnl::Vector3(1, 0, 0), tnl::ToRadian(-90));
	ceiling->rot_ = tnl::Quaternion::RotationAxis(tnl::Vector3(1, 0, 0), tnl::ToRadian(-90));
}

BackGroudStage::BackGroudStage(tnl::Vector3 pos, std::shared_ptr<dxe::Mesh> clonePlane)
{
	floor = clonePlane;
	texture = dxe::Texture::CreateFromFile("graphics/soil.jpg");
	floor->setTexture(texture);
	floor->pos_ = pos - tnl::Vector3(0, StageWall::BLOCKHIGHT / 2, 0);
	floor->rot_ = tnl::Quaternion::RotationAxis(tnl::Vector3(1, 0, 0), tnl::ToRadian(-90));

}

BackGroudStage::~BackGroudStage()
{
}

void BackGroudStage::Draw(std::shared_ptr<GameCamera>gamecamera) {
	if(floor)floor->render(gamecamera);
	if(ceiling)ceiling->render(gamecamera);
};