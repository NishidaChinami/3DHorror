#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"

class Message
{
public:
	enum class Title {
		OVERVIEW,
		OMEN,
		ARTICAL1,
		ARTICAL2,
		ARTICAL3,
		ARTICAL4
	};
	struct Content
	{
		Title s_title;
		std::string s_scentence;

	};
	Message();
	~Message();
	void ChangeStory(int title);
	void MessageDraw();
private:
	std::vector<std::vector<tnl::CsvCell>> message_csv;
	std::list<Content>message_list;
	std::vector<std::string>message_string_vector;
};
