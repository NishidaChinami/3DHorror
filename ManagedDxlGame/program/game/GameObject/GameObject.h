#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class GameCamera;
//-------------------------------------------------------------------------------------------------//
//オブジェクトクラス
//ほかのオブジェクトの親クラス
// メッシュのポインタやサイズ、座標などをメンバ変数にもつ
//-------------------------------------------------------------------------------------------------//
class GameObject
{
public:
	GameObject() {};
	virtual~GameObject() {};
	//更新処理
	virtual void Update(float delta_time) {}
	//描画処理
	virtual void Draw(std::shared_ptr<GameCamera>gamecamera) {}
	//メッシュポインタ
	std::shared_ptr<dxe::Mesh>mesh = nullptr;
	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	inline tnl::Vector3 GetObjectSize() const{ return size; }
protected:
	//テクスチャーポインタ
	Shared<dxe::Texture> texture = nullptr;
	//オブジェクトのサイズ
	tnl::Vector3 size = { 0,0,0 };
	//オブジェクトが有効かどうか
	bool is_valid = true;
};
