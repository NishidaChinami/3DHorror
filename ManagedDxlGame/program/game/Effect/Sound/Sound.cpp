#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"
#include"Sound.h"
#include"../../UI/OptionParam.h"

Sound::Sound()
{
	//�T�E���h�̓ǂݎ��
	m_ss_csv = tnl::LoadCsv("csv/SS_Sound.csv");
	m_bgm_csv = tnl::LoadCsv("csv/BGM_Sound.csv");
	//3D�����̓ǂݍ���
	for (int i = 1; i < m_ss_csv.size(); i++) {
		std::string name = m_ss_csv[i][0].getString().c_str();
		std::string url = m_ss_csv[i][1].getString().c_str();
		//���̉����Ƃ��ēǂݍ���
		SetCreate3DSoundFlag(TRUE);
		int handle = LoadSoundMem(url.c_str());
		SetCreate3DSoundFlag(FALSE);
		//�T�E���h�̖��O�ƃn���h�����}�b�v��
		m_ss_hdl.try_emplace(name.c_str(), handle);
		//�n���h������ۑ�
		m_ss_namelist.emplace_back(name.c_str());
	}
	//�QD�����̓ǂݍ���
	for (int i = 1; i < m_bgm_csv.size(); i++) {
		std::string name = m_bgm_csv[i][0].getString().c_str();
		std::string url = m_bgm_csv[i][1].getString().c_str();
		int handle = LoadSoundMem(url.c_str());
		//�T�E���h�̖��O�ƃn���h�����}�b�v��
		m_bgm_hdl.try_emplace(name.c_str(), handle);
		//�n���h������ۑ�
		m_bgm_namelist.emplace_back(name.c_str());
	}
	
}

//------------------------------------------------------------------------------------------------------------
//�C���X�^���X����
Sound* Sound::GetInstance()
{
	static Sound* instance = nullptr;
	if (!instance) {
		instance = new Sound();
	}
	return instance;
}
//------------------------------------------------------------------------------------------------------------
//�B��̃C���X�^���X�̃f���[�g�֐�
void Sound::Destroy()
{
	delete GetInstance();
}

//------------------------------------------------------------------------------------------------------------
//���̉����̍Đ��ʒu�┽���̎d�����v�Z����֐�
void Sound::Sound3DUpdate(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot,tnl::Vector3 sound_pos,std::string sound_name, float radius,int preset) {
	//�T�E���h�n���h�������炤
	int sound_handle = m_ss_hdl[sound_name.c_str()];
	// ���X�i�[�̈ʒu�ƌ�����ݒ�
	Set3DSoundListenerPosAndFrontPos_UpVecY(cf::ConvertToV3(listener_pos), VAdd(cf::ConvertToV3(listener_pos), cf::ConvertV4ToV3(listner_rot)));
	// �����������鋗����ݒ肷��
	Set3DRadiusSoundMem(radius, sound_handle);

	// ���̍Đ��ʒu��ݒ�
	Set3DPositionSoundMem(cf::ConvertToV3(sound_pos), sound_handle);

	// ���o�[�u�G�t�F�N�g�p�����[�^���v���Z�b�g�u���_�a���Ҏ��v���g�p���Đݒ�
	Set3DPresetReverbParamSoundMem(preset, sound_handle);

	//���������̐ݒ�
	//float atten_volume = 0;
	//�������鉹�̑傫�� = ����(255)-20(loge(����/�����̑傫��))/loge10�Ŏ�����邽��
	//atten_volume = OptionParam::GetInstance()->sound_volume -20 * (log((listener_pos - sound_pos).length() / 30)) / log(10);
}
//------------------------------------------------------------------------------------------------------------
//2D�������Đ�
void Sound::Sound2DPlay(std::string sound_name, int playtype) {
	int sound_handle = m_bgm_hdl[sound_name.c_str()];
	PlaySoundMem(sound_handle, playtype);
}
//------------------------------------------------------------------------------------------------------------
//3D�������Đ�
void Sound::Sound3DPlay(std::string sound_name, int playtype)
{
	int sound_handle = m_ss_hdl[sound_name.c_str()];
	PlaySoundMem(sound_handle, playtype);
}
//------------------------------------------------------------------------------------------------------------
//�T�E���h�̍Đ�
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
//�Đ������m���߂�
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
//�Đ����~�߂�
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
//���ʂ̒���
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
