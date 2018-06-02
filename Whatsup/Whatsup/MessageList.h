#pragma once   //_____________________________________________ MessageList.h  
#include "resource.h"

class MessageList : public Web::Page
{
public:
	MessageList()
	{
	}
	~MessageList()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceMessageList;
protected:
	void InitializeGui()
	{
		this->ID=L"MessageList";
		this->Title=L"MessageList";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"MessageList.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceMessageList.ID=L"serviceMessageList";
		this->serviceMessageList.Text=L"MessageList";
		this->AddChild(serviceMessageList);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
