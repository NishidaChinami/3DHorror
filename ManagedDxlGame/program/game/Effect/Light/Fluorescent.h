#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../../GameObject/GameObject.h"


class GameCamera;

class Fluorescent : public GameObject
{
public:
	Fluorescent(tnl::Vector3 pos);
	~Fluorescent();
	void Update(float delta_time)override;
	void Draw(std::shared_ptr<GameCamera>gamecamera)override;

	
private:

	tnl::Sequence<Fluorescent> sequence_ = tnl::Sequence<Fluorescent>(this, &Fluorescent::seqRed);
	bool seqRed(const float delta_time);
	bool seqNormal(const float delta_time);
	bool seqBlink(const float delta_time);

	
	//�u�����̃n���h��
	int fluorescent_hdl;
	//�u�����̌���͈�
	float Range = 500;
	//�����̋��������̕ϐ�
	float Atten0 = 0;
	float Atten1 = 0.0006;
	float Atten2 = 0.0f;

	//�t�F�[�h�̑��x�ϐ�
	float trans_time = 10.0f;
	//�_�ł̃J�E���g
	float blink_count = 0;
	//�_�ł̊Ԋu
	const float seconds = 3.0f;
};

