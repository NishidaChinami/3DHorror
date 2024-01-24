#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Sound
{
public:
	Sound();
	~Sound();

	enum class SoundList {
		WALK,
		RUN,
		ENEMYAPPROACHING,
		BREATHLESSNESS,
		LOCKER,
		HEARTBEAT,
		SOUNDLISTMAX

	};
	

	enum class BGMList {
		OPNING,
		GAMEBGM,
		CHASE,
		ENDING,
		SETTING
	};

	//3D音響Play
	//第1引数　聞き手の位置
	//第2引数　聞き手の向き
	//第3引数　音の位置
	//第4引数　音の聞こえる半径
	//第5引数　音のハンドルの名前
	//第6引数　リバーブのパラメーター（マクロ）
	//第7引数　サウンドのタイプ（マクロ）
	void Sound3DPlay(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot, tnl::Vector3 sound_pos, std::string sound_name, float radius = 256.0f, int preset = DX_REVERB_PRESET_PADDEDCELL, int playtype = DX_PLAYTYPE_LOOP);
	
	//2D音響Play
	void Sound2DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);
	//サウンドの再生
	void SoundPlay(std::string sound_name,int playtype = DX_PLAYTYPE_LOOP);
	//再生中かどうかを返す
	bool SoundPlaying(std::string sound_name);


	//再生中止
	void SoundStop(std::string sound_name);

	void Update(std::string sound_name,tnl::Vector3 pos);
	void ChangeVolume();
	//サウンドハンドルベクター
	std::unordered_map<std::string, int>SS_SoundHandle;
	std::unordered_map<std::string, int >BGM_SoundHandle;

private:
	//soundのcsvハンドル
	std::vector<std::vector<tnl::CsvCell>> ss_sound_csv;	
	std::vector<std::vector<tnl::CsvCell>> bgm_sound_csv;

	std::list<std::string> m_ss_list;
	std::list<std::string>m_bgm_list;
};

