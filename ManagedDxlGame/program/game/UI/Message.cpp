#include "../dxlib_ext/dxlib_ext.h"
#include"Message.h"

Message::Message()
{
	//csv����X�g�[���[��ǂݍ���
	m_message_csv = tnl::LoadCsv("csv/message.csv");
	for (int i = 0; i < m_message_csv.size(); i++) {
		int title = m_message_csv[i][1].getInt();
		std::string sentence = m_message_csv[i][2].getString().c_str();
		//Content�X�g���N�^�̃x�N�^�[�ɓ���ĕۑ�
		m_message_list.emplace_back(static_cast<Title>(title), sentence);
	}
}

Message::~Message()
{
}
//------------------------------------------------------------------------------------------------------------
//�\������X�g�[���[��؂�ւ���֐�
void Message::ChangeStory(int title) {
	//�\�����镶������x���Z�b�g
	m_message_string_vector.clear();
	m_now_title = static_cast<Title>(title);
	//�X�g�[���[���X�g����\��������̂����𒊏o
	auto mess = m_message_list.begin();
	while (mess != m_message_list.end())
	{
		if (mess->s_title == static_cast<Title>(title)) {
			m_message_string_vector.emplace_back(mess->s_scentence);
		}
		mess++;
	}
}
//------------------------------------------------------------------------------------------------------------
//�����̕`��
void Message::MessageDraw() {
	for (int i = 0; i < m_message_string_vector.size(); i++) {
		tnl::Vector3 pos = { MESSAGE_POS.x,MESSAGE_POS.y + i * 50.0f,0 };
		cf::DrawCenterString(m_message_string_vector[i], pos);
	}
	SetFontSize(FONT_SIZE);
	cf::DrawCenterString(CLOSE_MESS, CLOSE_POS);
}