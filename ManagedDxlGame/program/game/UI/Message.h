#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Mylibrary/Conversion.h"

//-------------------------------------------------------------------------------------------------//
//文章を管理するクラス
// ストーリーなどを表示する
//-------------------------------------------------------------------------------------------------//
class Message
{
public:
	//ストーリーの種類のEnumクラス
	enum class Title {
		OVERVIEW,
		ARTICAL1,
		ARTICAL2,
		ARTICAL3,
		ARTICAL4
	};
	//ストーリーの種類と文字をセットで保存しておくストラクタ
	struct Content
	{
		Title s_title;
		std::string s_scentence;

	};

	Message();
	~Message();
	//表示するストーリーを決める関数
	void ChangeStory(int title);
	//文字を描画する関数
	void MessageDraw();
	//-----------------------------------------Getter/Setter-----------------------------------------------------//
	TNL_PROPERTY(Title, TitleType, m_now_title);
private:
	//ストーリーを持つcsvの読み込むようベクター
	std::vector<std::vector<tnl::CsvCell>> m_message_csv;
	//Contentクラスのリスト　csvから文字とストーリーの種類を保存しておく
	std::list<Content>m_message_list;
	//表示するメッセージのベクター
	std::vector<std::string>m_message_string_vector;
	//今のストーリーの取得
	Title m_now_title = Title::OVERVIEW;

	//----------------------定数------------------------//
	const tnl::Vector3 MESSAGE_POS = { 640,200,0 };
};
