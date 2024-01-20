#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Sound.h"

Sound::Sound()
{
	//サウンドの読み取り
	ss_sound_csv = tnl::LoadCsv("csv/SS_Sound.csv");
	bgm_sound_csv = tnl::LoadCsv("csv/BGM_Sound.csv");
	for (int i = 1; i < ss_sound_csv.size(); i++) {
		std::string name = ss_sound_csv[i][0].getString().c_str();
		std::string url = ss_sound_csv[i][1].getString().c_str();
		SetCreate3DSoundFlag(TRUE);
		int handle = LoadSoundMem(url.c_str());
		SetCreate3DSoundFlag(FALSE);
		SS_SoundHandle.try_emplace(name.c_str(), handle);
	}

	
}

Sound::~Sound()
{
	//全部デリートする
}

void Sound::Sound3DPlay(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot,tnl::Vector3 sound_pos,std::string sound_name, float radius,int preset, int playtype) {
	//同じ中身示す？
	int sound_handle = SS_SoundHandle[sound_name.c_str()];
	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(cf::ConvertToV3(listener_pos), VAdd(cf::ConvertToV3(listener_pos), cf::ConvertV4ToV3(listner_rot)));
	// 音が聞こえる距離を設定する
	Set3DRadiusSoundMem(radius, sound_handle);

	// 音の再生位置を設定
	Set3DPositionSoundMem(cf::ConvertToV3(sound_pos), sound_handle);

	// リバーブエフェクトパラメータをプリセット「精神病患者室」を使用して設定
	Set3DPresetReverbParamSoundMem(preset, sound_handle);

	// 音の再生を開始
	//PlaySoundMem(sound_handle, playtype);
}

void Sound::Sound2DPlay(std::string sound_name, int playtype) {
	int sound_handle = BGM_SoundHandle[sound_name.c_str()];
	PlaySoundMem(sound_handle, playtype);
}

//サウンドの再生
void Sound::SoundPlay(std::string sound_name, int playtype) {
	auto it = BGM_SoundHandle.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != BGM_SoundHandle.end()) {
		sound_handle = BGM_SoundHandle[sound_name];
	}
	auto itr = SS_SoundHandle.find(sound_name.c_str());
	if (itr != SS_SoundHandle.end()) {
		sound_handle = SS_SoundHandle[sound_name];
	}

	PlaySoundMem(sound_handle, playtype);
}

//再生中か確かめる
bool Sound::SoundPlaying(std::string sound_name) {
	auto it = BGM_SoundHandle.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != BGM_SoundHandle.end()) {
		sound_handle = BGM_SoundHandle[sound_name];
	}
	auto itr = SS_SoundHandle.find(sound_name.c_str());
	if (itr != SS_SoundHandle.end()) {
		sound_handle = SS_SoundHandle[sound_name];
	}
	if (1 == CheckSoundMem(sound_handle))return true;
	else return false;
}

//StopSoundMem
void Sound::SoundStop(std::string sound_name) {
	auto it = BGM_SoundHandle.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != BGM_SoundHandle.end()) {
		sound_handle = BGM_SoundHandle[sound_name];
	}
	auto itr = SS_SoundHandle.find(sound_name.c_str());
	if (itr != SS_SoundHandle.end()) {
		sound_handle = SS_SoundHandle[sound_name];
	}

	StopSoundMem(sound_handle);
}

void Sound::Update(std::string sound_name,tnl::Vector3 pos) {
	int sound_handle = SS_SoundHandle[sound_name.c_str()];
	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(cf::ConvertToV3(tnl::Vector3(0,0,0)), VAdd(cf::ConvertToV3(tnl::Vector3(0, 0, 0)), cf::ConvertV4ToV3(tnl::Quaternion(0,0,-1,0))));
	// 音が聞こえる距離を設定する
	Set3DRadiusSoundMem(256.0f, sound_handle);

	// 音の再生位置を設定
	Set3DPositionSoundMem(cf::ConvertToV3(pos), sound_handle);

	// リバーブエフェクトパラメータをプリセット「精神病患者室」を使用して設定
	Set3DPresetReverbParamSoundMem(DX_REVERB_PRESET_PADDEDCELL, sound_handle);

	// 音の再生を開始
	PlaySoundMem(sound_handle, DX_PLAYTYPE_LOOP);
}