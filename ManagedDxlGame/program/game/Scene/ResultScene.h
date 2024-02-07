#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"

//-------------------------------------------------------------------------------------------------//
//���U���g�N���X
// �V�[���̃G���f�B���O���̕`��
//-------------------------------------------------------------------------------------------------//
class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	//�V�[���̍X�V
	void Update(float delta_time)override;
	//�V�[���̕`��֐�
	void Draw()override;
private:
	//�G���f�B���O�̔w�i�ƕ����̕ۑ�����ϐ�
	int m_background_hdl = 0;
	std::string letter;
	
	//�Q�[���N���A�ƃQ�[���I�[�o�[�̔w�i�n���h��
	int m_deathgpc_hdl = 0;
	int m_cleargpc_hdl = 0;

	//----------------------�萔------------------------//
	static const int SELECT_NUM = 2;
	//���U���g�Ŏg������
	const std::string DEATH = { "���Ȃ��͎���" };
	const std::string SERECT[SELECT_NUM] = { "�^�C�g���֖߂�","������x�v���C" };
	const std::string CLEAR = { "�Q�[���N���A" };
	//�e�����̍��W
	const tnl::Vector3 CENTER_POS = { 640,360,0 };
	const tnl::Vector3 TITLE_POS = { 540, 600,0 };
	const tnl::Vector3 REPLAY_POS = { 740,600,0 };
	//�����̓����蔻��̃T�C�Y
	const tnl::Vector3 LETTER_SIZE = { 100,50,0 };
	//�����̃t�H���g�T�C�Y
	const float RESULT_FONT_SIZE = 50;
	const float SELECT_FONT_SIZE = 20;
};

