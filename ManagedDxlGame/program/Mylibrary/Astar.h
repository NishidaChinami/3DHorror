#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"maze.h"

namespace astar {


	// �}�b�v�X�e�[�^�X
	// �o�H�T���p�m�[�h
	enum class TrackState {
		OPEN,
		CLOSED,
		ROAD,      // ��
		NONE,
		START,      // �X�^�[�g
		END       // �S�[��
	};

	class Node {
	public:
		Node() :
			status(TrackState::NONE),
			cost_real(0),
			cost_guess(0),
			score(0),
			parent(nullptr)
		{}


		tnl::Vector2i pos;  // 2�����z���̍��W
		TrackState status;//���������}�b�v����State���Ƃ�
		int cost_real;     // ���R�X�g
		int cost_guess;    // ����R�X�g
		int score;         // �X�R�A
		Node* parent;      // �e�m�[�h( �Ō�ɃS�[������H�邽�� )

		bool operator < (const Node& node) const {
			return score > node.score;
		}

	};

	class Path
	{
	public:
		Path() {};
		~Path() {};

		// �w����W���L����( OPEN �\�� )�}�b�v�ʒu���ǂ�������
		//��1���� ���ׂ������W
		//��Q�����@Node�N���X�̂Q�����z��|�C���^
		//��3�E4�����@�ŒZ�o�H�����߂����}�b�v�̉��Əc��̐�
		bool IsEnableMapPosition(tnl::Vector2i pos, Node** _nodes,int row,int col);

		// [ ���݃I�[�v���ɂȂ��Ă���m�[�h�ň�ԃX�R�A�̏��������̂��擾 ]
		// �T���v���̕�����Ղ��D��Ȃ̂őS�m�[�h�𒲂ׂ�`�ɂ��Ă��邪�A
		// �����͗ǂ��Ȃ��̂Ń��C�u���������鎞�ɂł� ���ɃI�[�v�����Ă���
		// �m�[�h�������ׂ�悤�Ɍ�������}���������悢
		Node* GetSmallScoreNodeFromOpenNodes(Node** _nodes, int row, int col);


		// �o�H�T�� Astar�A���S���Y��
		bool Aster(Node** _nodes, Node* _now, std::vector<Node*>* _route,int row ,int col);


	};


}