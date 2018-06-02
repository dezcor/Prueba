#pragma once   //_____________________________________________ SendMessage.h  
#include "resource.h"

class SendMessagex : public Web::Page
{
public:
	SendMessagex()
	{
	}
	~SendMessagex()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceSendMessage;
protected:
	void InitializeGui()
	{
		this->ID=L"SendMessage";
		this->Title=L"SendMessage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"SendMessagex.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceSendMessage.ID=L"serviceSendMessage";
		this->serviceSendMessage.Text=L"SendMessage";
		this->AddChild(serviceSendMessage);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
