#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace cf {


	//QuaternionからDxlibの3D関数に使えるVector3型に変換
	//第1引数　Quaternion
	VECTOR  ConvertV4ToV3(tnl::Quaternion rot);


	// tnl::Vector3をVECTORに変換する
   // 第1引数 tnl::Vector3
	VECTOR ConvertToV3(const tnl::Vector3& tnl_pos);

	//２次元配列の位置をPosから求める
	tnl::Vector2i GridPos(const tnl::Vector3& pos, const tnl::Vector3& startpos, int size);
	//マップの配列から座標を求める
	//第1引数　配列の要素数をもつVector2Int
	//第2引数　マップの一マスのサイズ
	//第3引数　床の高さ
	tnl::Vector3 Coordinate(tnl::Vector2i gridpos, const tnl::Vector3& startpos, int size, float hight = 0);

	//何キーが押されているか
	eKeys GetPushKey();

	//マウスカーソルとの当たり判定
	//第1引数　当たり判定の対象の座標
	//第2引数　当たり判定の対象のサイズ
	//ret マウスと当たったかどうか
	bool IntersectMouse(const tnl::Vector3 &pos, const tnl::Vector3 &size);

	//文字を中央に表示する
	//第1引数　文字列
	//第2引数　文字の位置
	void DrawCenterString(const std::string &letter, const tnl::Vector3 &pos);
}