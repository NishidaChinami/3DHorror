#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"BaseScene.h"


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
	int m_backgroud_hdl = 0;
	std::string letter;


	int m_deathgpc_hdl = 0;
	int m_cleargpc_hdl = 0;
	static const int SELECT_NUM = 2;
	//�����̓ǂݍ��݂Ɏ��s����H
	const std::string DEATH = { "���Ȃ��͎���" };
	const std::string SERECT[SELECT_NUM] = { "������x�v���C","�^�C�g���֖߂�" };
	const std::string CLEAR = { "�Q�[���N���A" };

	const tnl::Vector3 CENTER_POS = { 300,360,0 };
	const tnl::Vector3 TITLE_POS = { 200, 600,0 };
	const tnl::Vector3 REPLAY_POS = { 500,600,0 };

	const tnl::Vector3 LETTER_SIZE = { 100,50,0 };
};

