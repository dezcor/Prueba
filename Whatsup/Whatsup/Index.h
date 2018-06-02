#pragma once   //_____________________________________________ Index.h  
#include "resource.h"

class Index : public Web::Page
{
public:
	Index()
	{
	}
	~Index()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Button btContactList;
	Web::Button btSendMessage;
	Web::Button btMessageList;
	Web::Button btDeleteMessage;
	Web::Button btNewUser;
	Web::Button btAddContacto;
	Web::Button btLogin;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->btContactList.ID=L"btContactList";
		this->btSendMessage.ID=L"btSendMessage";
		this->btMessageList.ID=L"btMessageList";
		this->btDeleteMessage.ID=L"btDeleteMessage";
		this->btNewUser.ID=L"btNewUser";
		this->btAddContacto.ID=L"btAddContacto";
		this->btLogin.ID=L"btLogin";
		this->btContactList.Text=L"ContactList";
		this->btSendMessage.Text=L"Send Message";
		this->btMessageList.Text=L"Message List";
		this->btDeleteMessage.Text=L"Delete Message";
		this->btNewUser.Text=L"NewUser";
		this->btAddContacto.Text=L"AddContacto";
		this->btLogin.Text=L"Login";
		this->btContactList.EndHtml=L"&nbsp;";
		this->btSendMessage.EndHtml=L"&nbsp;";
		this->btMessageList.EndHtml=L"&nbsp;";
		this->btDeleteMessage.EndHtml=L"&nbsp;";
		this->btNewUser.EndHtml=L"&nbsp;";
		this->btAddContacto.EndHtml=L"&nbsp;";
		this->AddChild(btContactList);
		this->AddChild(btSendMessage);
		this->AddChild(btMessageList);
		this->AddChild(btDeleteMessage);
		this->AddChild(btNewUser);
		this->AddChild(btAddContacto);
		this->AddChild(btLogin);
	}
	//_________________________________________________
	void btContactList_onclick(Web::HttpConnector& h);
	void btSendMessage_onclick(Web::HttpConnector& h);
	void btMessageList_onclick(Web::HttpConnector& h);
	void btDeleteMessage_onclick(Web::HttpConnector& h);
	void btNewUser_onclick(Web::HttpConnector& h);
	void btAddContacto_onclick(Web::HttpConnector& h);
	void btLogin_onclick(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btContactList.IsEvent(h, LEX_HTML_ONCLICK)) {btContactList_onclick(h);}
		if (btSendMessage.IsEvent(h, LEX_HTML_ONCLICK)) {btSendMessage_onclick(h);}
		if (btMessageList.IsEvent(h, LEX_HTML_ONCLICK)) {btMessageList_onclick(h);}
		if (btDeleteMessage.IsEvent(h, LEX_HTML_ONCLICK)) {btDeleteMessage_onclick(h);}
		if (btNewUser.IsEvent(h, LEX_HTML_ONCLICK)) {btNewUser_onclick(h);}
		if (btAddContacto.IsEvent(h, LEX_HTML_ONCLICK)) {btAddContacto_onclick(h);}
		if (btLogin.IsEvent(h, LEX_HTML_ONCLICK)) {btLogin_onclick(h);}
	}
};
