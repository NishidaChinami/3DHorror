#pragma once
//-------------------------------------------------------------------------------------------------//
//Scene�̐e�N���X
//-------------------------------------------------------------------------------------------------//
class BaseScene {
public:
	BaseScene() {};
	virtual~BaseScene() {};
	//�V�[���̍X�V
	virtual void Update(float delta_time) {};
	//�V�[���̕`��֐�
	virtual void Draw() {};
protected:
	//�X�N���[���G�t�F�N�g�̃|�C���^
	Shared<dxe::ScreenEffect> screen_efct = nullptr;
};