#pragma once
//-------------------------------------------------------------------------------------------------//
//Scene�̐e�N���X
//-------------------------------------------------------------------------------------------------//
class BaseScene {
public:
	BaseScene() {};
	virtual~BaseScene() {};
	virtual void Update(float delta_time) {};//�V�[���̍X�V
	virtual void Draw() {};//�V�[���̕`��֐�
};