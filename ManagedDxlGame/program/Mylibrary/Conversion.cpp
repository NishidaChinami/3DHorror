#include "../dxlib_ext/dxlib_ext.h"
#include"Conversion.h"

namespace cf {
	//QuaternionからDxlibの3D関数に使えるVector3型に変換
	VECTOR  ConvertV4ToV3(tnl::Quaternion rot) {
		tnl::Vector3 v3_rot = rot.getEuler();
		return { TNL_DEP_V3(v3_rot) };
	}

	//tnl::Vector3をVECTORに変換する
	VECTOR ConvertToV3(const tnl::Vector3& tnl_pos)
	{
		return VGet(tnl_pos.x, tnl_pos.y, tnl_pos.z);
	}

	//２次元配列の位置をPosから求める
	tnl::Vector2i GridPos(const tnl::Vector3& pos, const tnl::Vector3& startpos, int size) {
		int x = 0;
		int y = 0;
		x = (pos.x - startpos.x + size/2) / size;
		y = (pos.z - startpos.z + size/2) / size;
		return tnl::Vector2i(x, y); 
	}

	//マップの配列から座標を求める
	tnl::Vector3 Coordinate(tnl::Vector2i gridpos, const tnl::Vector3& startpos, int size, float hight) {
		tnl::Vector3 position;
		position.x = gridpos.x * size +startpos.x;
		position.y = hight;
		position.z = gridpos.y * size + startpos.z;
		return position;
	}

	eKeys GetPushKey() {
		if (tnl::Input::IsKeyDown(eKeys::KB_W))return eKeys::KB_W;
		if (tnl::Input::IsKeyDown(eKeys::KB_A))return eKeys::KB_A;
		if (tnl::Input::IsKeyDown(eKeys::KB_D))return eKeys::KB_D;
		if (tnl::Input::IsKeyDown(eKeys::KB_S))return eKeys::KB_S;
		return eKeys::KB_0;
	}
	//マウスとの当たり判定
	bool IntersectMouse(const tnl::Vector3& pos, const tnl::Vector3& size) {
		tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
		if (mouse_pos.x <= pos.x + size.x / 2 &&
			mouse_pos.x >= pos.x - size.x / 2 &&
			mouse_pos.y <= pos.y + size.y / 2 &&
			mouse_pos.y >= pos.y - size.y / 2) {
			return true;
		}
	
		return false;
	}

	void DrawCenterString(const std::string& letter, const tnl::Vector3& pos) {
		int width = GetDrawStringWidth(letter.c_str(), letter.length()) / 2;
		DrawStringEx(pos.x - width, pos.y , -1, "%s", letter.c_str());
	}


}