#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"

//-------------------------------------------------------------------------------------------------//
//���͂��Ǘ�����N���X
// �X�g�[���[�Ȃǂ�\������
//-------------------------------------------------------------------------------------------------//
class Message
{
public:
	//�X�g�[���[�̎�ނ�Enum�N���X
	enum class Title {
		OVERVIEW,
		ARTICAL1,
		ARTICAL2,
		ARTICAL3,
		ARTICAL4
	};
	//�X�g�[���[�̎�ނƕ������Z�b�g�ŕۑ����Ă����X�g���N�^
	struct Content
	{
		Title s_title;
		std::string s_scentence;

	};

	Message();
	~Message();
	//�\������X�g�[���[�����߂�֐�
	void ChangeStory(int title);
	//������`�悷��֐�
	void MessageDraw();
	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	TNL_PROPERTY(Title, TitleType, m_now_title);
private:
	//�X�g�[���[������csv�̓ǂݍ��ނ悤�x�N�^�[
	std::vector<std::vector<tnl::CsvCell>> m_message_csv;
	//Content�N���X�̃��X�g�@csv���當���ƃX�g�[���[�̎�ނ�ۑ����Ă���
	std::list<Content>m_message_list;
	//�\�����郁�b�Z�[�W�̃x�N�^�[
	std::vector<std::string>m_message_string_vector;
	//���̃X�g�[���[�̎擾
	Title m_now_title = Title::OVERVIEW;

	//----------------------�萔------------------------//
	const tnl::Vector3 MESSAGE_POS = { 640,200,0 };
};
