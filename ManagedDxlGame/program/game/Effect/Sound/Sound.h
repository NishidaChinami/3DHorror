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

	//3D����Play
	//��1�����@������̈ʒu
	//��2�����@������̌���
	//��3�����@���̈ʒu
	//��4�����@���̕������锼�a
	//��5�����@���̃n���h���̖��O
	//��6�����@���o�[�u�̃p�����[�^�[�i�}�N���j
	//��7�����@�T�E���h�̃^�C�v�i�}�N���j
	void Sound3DPlay(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot, tnl::Vector3 sound_pos, std::string sound_name, float radius = 256.0f, int preset = DX_REVERB_PRESET_PADDEDCELL, int playtype = DX_PLAYTYPE_LOOP);
	
	//2D����Play
	void Sound2DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);
	//�T�E���h�̍Đ�
	void SoundPlay(std::string sound_name,int playtype = DX_PLAYTYPE_LOOP);
	//�Đ������ǂ�����Ԃ�
	bool SoundPlaying(std::string sound_name);


	//�Đ����~
	void SoundStop(std::string sound_name);

	void Update(std::string sound_name,tnl::Vector3 pos);
	void ChangeVolume();
	//�T�E���h�n���h���x�N�^�[
	std::unordered_map<std::string, int>SS_SoundHandle;
	std::unordered_map<std::string, int >BGM_SoundHandle;

private:
	//sound��csv�n���h��
	std::vector<std::vector<tnl::CsvCell>> ss_sound_csv;	
	std::vector<std::vector<tnl::CsvCell>> bgm_sound_csv;

	std::list<std::string> m_ss_list;
	std::list<std::string>m_bgm_list;
};

