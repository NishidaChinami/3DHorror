#pragma once
#include "../dxlib_ext/dxlib_ext.h"

//-------------------------------------------------------------------------------------------------//
//�T�E���h���Ǘ�����N���X
// �V���O���g���p�^�[�����g�p
//-------------------------------------------------------------------------------------------------//
class Sound
{
public:
	//�V���O���g��
	static Sound* GetInstance();
	//�f�X�g���N�^�֐�
	static void Destroy();

	//3D�����̍Đ��ʒu��͈͂��Z�b�g����֐�
	//��1�����@������̈ʒu
	//��2�����@������̌���
	//��3�����@���̈ʒu
	//��4�����@���̕������锼�a
	//��5�����@���̃n���h���̖��O
	//��6�����@���o�[�u�̃p�����[�^�[�i�}�N���j
	void Sound3DUpdate(tnl::Vector3 listener_pos, tnl::Quaternion listner_rot, tnl::Vector3 sound_pos, std::string sound_name, float radius = 256.0f, int preset = DX_REVERB_PRESET_PADDEDCELL);
	
	//2D����Play
	//��1�����@���̃n���h����
	//��2�����@�T�E���h�̃^�C�v�i�}�N���j
	void Sound2DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);
	//3D����Play
	//��1�����@���̃n���h����
	//��2�����@�T�E���h�̃^�C�v�i�}�N���j
	void Sound3DPlay(std::string sound_name, int playtype = DX_PLAYTYPE_LOOP);

	//�T�E���h�̍Đ� 2D,3D����
	//��1�����@���̃n���h����
	//��2�����@�T�E���h�̃^�C�v�i�}�N���j
	void SoundPlay(std::string sound_name,int playtype = DX_PLAYTYPE_LOOP);

	//�Đ������ǂ�����Ԃ�
	//��1�����@�Đ������m���߂������̃n���h����
	bool SoundPlaying(std::string sound_name);


	//�Đ����~
	//��1���� �Đ����~�߂������̃n���h����
	void SoundStop(std::string sound_name);

	//���ʂ�ύX���鏈��
	void ChangeVolume();

private:
	Sound();
	//�T�E���h�n���h���}�b�v
	std::unordered_map<std::string, int>m_ss_hdl;
	std::unordered_map<std::string, int >m_bgm_hdl;
	//sound��csv��ǂݍ��ރx�N�^�[
	std::vector<std::vector<tnl::CsvCell>> m_ss_csv;	
	std::vector<std::vector<tnl::CsvCell>> m_bgm_csv;
	//�T�E���h�̖��O���X�g
	std::list<std::string> m_ss_namelist;
	std::list<std::string>m_bgm_namelist;
};

