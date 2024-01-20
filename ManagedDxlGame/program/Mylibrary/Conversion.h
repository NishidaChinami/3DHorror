#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace cf {


	//Quaternion����Dxlib��3D�֐��Ɏg����Vector3�^�ɕϊ�
	//��1�����@Quaternion
	VECTOR  ConvertV4ToV3(tnl::Quaternion rot);


	// tnl::Vector3��VECTOR�ɕϊ�����
   // ��1���� tnl::Vector3
	VECTOR ConvertToV3(const tnl::Vector3& tnl_pos);

	//�Q�����z��̈ʒu��Pos���狁�߂�
	tnl::Vector2i GridPos(const tnl::Vector3& pos, const tnl::Vector3& startpos, int size);
	//�}�b�v�̔z�񂩂���W�����߂�
	//��1�����@�z��̗v�f��������Vector2Int
	//��2�����@�}�b�v�̈�}�X�̃T�C�Y
	//��3�����@���̍���
	tnl::Vector3 Coordinate(tnl::Vector2i gridpos, const tnl::Vector3& startpos, int size, float hight = 0);

	//���L�[��������Ă��邩
	eKeys GetPushKey();

	//�}�E�X�J�[�\���Ƃ̓����蔻��
	//��1�����@�����蔻��̑Ώۂ̍��W
	//��2�����@�����蔻��̑Ώۂ̃T�C�Y
	//ret �}�E�X�Ɠ����������ǂ���
	bool IntersectMouse(const tnl::Vector3 &pos, const tnl::Vector3 &size);

	//�����𒆉��ɕ\������
	//��1�����@������
	//��2�����@�����̈ʒu
	void DrawCenterString(const std::string &letter, const tnl::Vector3 &pos);
}