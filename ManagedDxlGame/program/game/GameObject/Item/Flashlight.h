#pragma once
#include "../dxlib_ext/dxlib_ext.h"



class Flashlight
{
public:
	Flashlight();
	~Flashlight();
	void Update(tnl::Vector3 pos, tnl::Quaternion rot);
	bool GetIsAlive()const { return is_alive; }

private:
	int falshlight_hdl;
	float Range = 1000;
	float Atten0 = 0;
	float Atten1 = 0.0006;
	float Atten2 = 0.0000f;
	float OutAngle = 90.0f;
	float InAngle = 45.0f;

	bool lightActive = true;
	bool is_alive = true;

};

