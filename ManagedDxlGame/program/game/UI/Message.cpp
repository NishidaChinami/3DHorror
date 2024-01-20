#include "../dxlib_ext/dxlib_ext.h"
#include"Message.h"

Message::Message()
{
	message_csv = tnl::LoadCsv("csv/message.csv");
	for (int i = 1; i < message_csv.size(); i++) {
		int title = message_csv[i][1].getInt();
		std::string sentence = message_csv[i][2].getString().c_str();
		message_list.emplace_back(static_cast<Title>(title), sentence);
	}
}

Message::~Message()
{
}

void Message::ChangeStory(int title) {
	message_string_vector.clear();
	auto mess = message_list.begin();
	while (mess != message_list.end())
	{
		if (mess->s_title == static_cast<Title>(title)) {
			message_string_vector.emplace_back(mess->s_scentence);
		}
		mess;
	}
}
void Message::MessageDraw() {
	for (int i = 0; i < message_string_vector.size(); i++) {
		tnl::Vector3 pos = { 340,200 + i * 50.0f,0 };
		cf::DrawCenterString(message_string_vector[i], pos);
	}
}