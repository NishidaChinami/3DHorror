#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Sound.h"
#include"../../UI/OptionParam.h"

Sound::Sound()
{
	//サウンドの読み取り
	m_ss_csv = tnl::LoadCsv("csv/SS_Sound.csv");
	m_bgm_csv = tnl::LoadCsv("csv/BGM_Sound.csv");
	//3D音響の読み込み
	for (int i = 1; i < m_ss_csv.size(); i++) {
		std::string name = m_ss_csv[i][0].getString().c_str();
		std::string url = m_ss_csv[i][1].getString().c_str();
		//立体音響として読み込む
		SetCreate3DSoundFlag(TRUE);
		int handle = LoadSoundMem(url.c_str());
		SetCreate3DSoundFlag(FALSE);
		//サウンドの名前とハンドルをマップへ
		m_ss_hdl.try_emplace(name.c_str(), handle);
		//ハンドル名を保存
		m_ss_namelist.emplace_back(name.c_str());
	}
	//２D音響の読み込み
	for (int i = 1; i < m_bgm_csv.size(); i++) {
		std::string name = m_bgm_csv[i][0].getString().c_str();
		std::string url = m_bgm_csv[i][1].getString().c_str();
		int handle = LoadSoundMem(url.c_str());
		//サウンドの名前とハンドルをマップへ
		m_bgm_hdl.try_emplace(name.c_str(), handle);
		//ハンドル名を保存
		m_bgm_namelist.emplace_back(name.c_str());
	}
	
}

//------------------------------------------------------------------------------------------------------------
//インスタンス生成
Sound* Sound::GetInstance()
{
	static Sound* instance = nullptr;
	if (!instance) {
		instance = new Sound();
	}
	return instance;
}
//------------------------------------------------------------------------------------------------------------
//唯一のインスタンスのデリート関数
void Sound::Destroy()
{
	delete GetInstance();
}

//------------------------------------------------------------------------------------------------------------
//立体音響の再生位置や反響の仕方を計算する関数
void Sound::Sound3DUpdate(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot,tnl::Vector3 sound_pos,std::string sound_name, float radius,int preset) {
	//サウンドハンドルをもらう
	int sound_handle = m_ss_hdl[sound_name.c_str()];
	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(cf::ConvertToV3(listener_pos), VAdd(cf::ConvertToV3(listener_pos), cf::ConvertV4ToV3(listner_rot)));
	// 音が聞こえる距離を設定する
	Set3DRadiusSoundMem(radius, sound_handle);

	// 音の再生位置を設定
	Set3DPositionSoundMem(cf::ConvertToV3(sound_pos), sound_handle);

	// リバーブエフェクトパラメータをプリセット「精神病患者室」を使用して設定
	Set3DPresetReverbParamSoundMem(preset, sound_handle);

	//距離減衰の設定
	//float atten_volume = 0;
	//聞こえる音の大きさ = 音源(255)-20(loge(距離/音源の大きさ))/loge10で示されるため
	//atten_volume = OptionParam::GetInstance()->sound_volume -20 * (log((listener_pos - sound_pos).length() / 30)) / log(10);
}
//------------------------------------------------------------------------------------------------------------
//2D音響を再生
void Sound::Sound2DPlay(std::string sound_name, int playtype) {
	int sound_handle = m_bgm_hdl[sound_name.c_str()];
	PlaySoundMem(sound_handle, playtype);
}
//------------------------------------------------------------------------------------------------------------
//3D音響を再生
void Sound::Sound3DPlay(std::string sound_name, int playtype)
{
	int sound_handle = m_ss_hdl[sound_name.c_str()];
	PlaySoundMem(sound_handle, playtype);
}
//------------------------------------------------------------------------------------------------------------
//サウンドの再生
void Sound::SoundPlay(std::string sound_name, int playtype) {
	auto it = m_bgm_hdl.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != m_bgm_hdl.end()) {
		sound_handle = m_bgm_hdl[sound_name.c_str()];
	}
	auto itr = m_ss_hdl.find(sound_name.c_str());
	if (itr != m_ss_hdl.end()) {
		sound_handle = m_ss_hdl[sound_name.c_str()];
	}

	PlaySoundMem(sound_handle, playtype);
}
//------------------------------------------------------------------------------------------------------------
//再生中か確かめる
bool Sound::SoundPlaying(std::string sound_name) {
	auto it = m_bgm_hdl.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != m_bgm_hdl.end()) {
		sound_handle = m_bgm_hdl[sound_name.c_str()];
	}
	auto itr = m_ss_hdl.find(sound_name.c_str());
	if (itr != m_ss_hdl.end()) {
		sound_handle = m_ss_hdl[sound_name.c_str()];
	}
	if (1 == CheckSoundMem(sound_handle)) {
		return true;
	}
	else return false;
}
//------------------------------------------------------------------------------------------------------------
//再生を止める
void Sound::SoundStop(std::string sound_name) {
	auto it = m_bgm_hdl.find(sound_name.c_str());
	int sound_handle = 0;
	if (it != m_bgm_hdl.end()) {
		sound_handle = m_bgm_hdl[sound_name.c_str()];
	}
	auto itr = m_ss_hdl.find(sound_name.c_str());
	if (itr != m_ss_hdl.end()) {
		sound_handle = m_ss_hdl[sound_name.c_str()];
	}

	StopSoundMem(sound_handle);
}
//------------------------------------------------------------------------------------------------------------
//音量の調整
void Sound::ChangeVolume()
{
	auto param = OptionParam::GetInstance();
	for (auto bgmhdl : m_bgm_namelist) {
		ChangeVolumeSoundMem(param->sound_volume, m_bgm_hdl[bgmhdl.c_str()]);
	}
	for (auto sshdl : m_ss_namelist) {
		ChangeVolumeSoundMem(param->sound_volume, m_bgm_hdl[sshdl.c_str()]);
	}
	
}
