#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Flashlight.h"

Flashlight::Flashlight()
{
	falshlight_hdl = CreateSpotLightHandle(VGet(0,0,0), VGet(0.0f, 0.0f, 1.0f), DX_PI_F / 4.0f, DX_PI_F / 6.0, Range, Atten0, Atten1, Atten2);
	SetLightDifColorHandle(falshlight_hdl, GetColorF(0.2f, 0.2f, 0.37f,0));
	SetLightAmbColorHandle(falshlight_hdl, GetColorF(0.2f, 0.2f, 0.2f, 0));
}

Flashlight::~Flashlight()
{
	DeleteLightHandle(falshlight_hdl);
}

//‰ù’†“d“”‚ÌON‚ÆOFF
void Flashlight::Update(tnl::Vector3 pos ,tnl::Quaternion rot) {
	//SetDrawBright(200, 200, 200);
	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		lightActive == true ? lightActive = false : lightActive = true;
	}
	SetLightEnableHandle(falshlight_hdl, lightActive);
	SetLightPositionHandle(falshlight_hdl, cf::ConvertToV3(pos));
	SetLightDirectionHandle(falshlight_hdl, cf::ConvertToV3(tnl::Vector3::TransformCoord({ 0,0,1 }, rot)));
}
