#pragma once   //_____________________________________________ Login.h  
#include "resource.h"

class Login: public Web::Page
{
public:
	Login()
	{
	}
	~Login()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
protected:
	void InitializeGui()
	{
		this->ID=L"Login";
		this->Title=L"Login";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Login.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
