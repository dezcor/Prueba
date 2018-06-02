#pragma once   //_____________________________________________ DeleteMessage.h  
#include "resource.h"

class DeleteMessage : public Web::Page
{
public:
	DeleteMessage()
	{
	}
	~DeleteMessage()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceDeleteMessage;
protected:
	void InitializeGui()
	{
		this->ID=L"DeleteMessage";
		this->Title=L"DeleteMessage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"DeleteMessage.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceDeleteMessage.ID=L"serviceDeleteMessage";
		this->serviceDeleteMessage.Text=L"DeleteMessage";
		this->AddChild(serviceDeleteMessage);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
