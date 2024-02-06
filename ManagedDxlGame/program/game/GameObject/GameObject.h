#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class GameCamera;
//-------------------------------------------------------------------------------------------------//
//�I�u�W�F�N�g�N���X
//�ق��̃I�u�W�F�N�g�̐e�N���X
// ���b�V���̃|�C���^��T�C�Y�A���W�Ȃǂ������o�ϐ��ɂ���
//-------------------------------------------------------------------------------------------------//
class GameObject
{
public:
	GameObject() {};
	virtual~GameObject() {};
	//�X�V����
	virtual void Update(float delta_time) {}
	//�`�揈��
	virtual void Draw(std::shared_ptr<GameCamera>gamecamera) {}
	//���b�V���|�C���^
	std::shared_ptr<dxe::Mesh>mesh = nullptr;
	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	inline tnl::Vector3 GetObjectSize() const{ return size; }
protected:
	//�e�N�X�`���[�|�C���^
	Shared<dxe::Texture> texture = nullptr;
	//�I�u�W�F�N�g�̃T�C�Y
	tnl::Vector3 size = { 0,0,0 };
	//�I�u�W�F�N�g���L�����ǂ���
	bool is_valid = true;
};
