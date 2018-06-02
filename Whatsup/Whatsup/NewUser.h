#pragma once   //_____________________________________________ NewUser.h  
#include "resource.h"

class NewUser: public Web::Page
{
public:
	NewUser()
	{
	}
	~NewUser()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceNewUser;
protected:
	void InitializeGui()
	{
		this->ID=L"NewUser";
		this->Title=L"NewUser";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"NewUser.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceNewUser.ID=L"serviceNewUser";
		this->serviceNewUser.Text=L"NewUser";
		this->AddChild(serviceNewUser);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
