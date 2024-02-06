#pragma once
#include "../dxlib_ext/dxlib_ext.h"

//-------------------------------------------------------------------------------------------------//
//サウンドを管理するクラス
// シングルトンパターンを使用
//-------------------------------------------------------------------------------------------------//
class Sound
{
public:
	//シングルトン
	static Sound* GetInstance();
	//デストラクタ関数
	static void Destroy();

	//3D音響の再生位置や範囲をセットする関数
	//第1引数　聞き手の位置
	//第2引数　聞き手の向き
	//第3引数　音の位置
	//第4引数　音の聞こえる半径
	//第5引数　音のハンドルの名前
	//第6引数　リバーブのパラメーター（マクロ）
	void Sound3DUpdate(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot, tnl::Vector3 sound_pos, std::string sound_name, float radius = 256.0f, int preset = DX_REVERB_PRESET_PADDEDCELL);
	
	//2D音響Play
	//第1引数　音のハンドル名
	//第2引数　サウンドのタイプ（マクロ）
	void Sound2DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);
	//3D音響Play
	//第1引数　音のハンドル名
	//第2引数　サウンドのタイプ（マクロ）
	void Sound3DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);

	//サウンドの再生 2D,3D両方
	//第1引数　音のハンドル名
	//第2引数　サウンドのタイプ（マクロ）
	void SoundPlay(std::string sound_name,int playtype = DX_PLAYTYPE_LOOP);

	//再生中かどうかを返す
	//第1引数　再生中か確かめたい音のハンドル名
	bool SoundPlaying(std::string sound_name);


	//再生中止
	//第1引数 再生を止めたい音のハンドル名
	void SoundStop(std::string sound_name);

	//音量を変更する処理
	void ChangeVolume();

private:
	Sound();
	//サウンドハンドルマップ
	std::unordered_map<std::string, int>m_ss_hdl;
	std::unordered_map<std::string, int >m_bgm_hdl;
	//soundのcsvを読み込むベクター
	std::vector<std::vector<tnl::CsvCell>> m_ss_csv;	
	std::vector<std::vector<tnl::CsvCell>> m_bgm_csv;
	//サウンドの名前リスト
	std::list<std::string> m_ss_namelist;
	std::list<std::string>m_bgm_namelist;
};

