#pragma once   //_____________________________________________ AddContacto.h  
#include "resource.h"

class AddContacto: public Web::Page
{
public:
	AddContacto()
	{
	}
	~AddContacto()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceAddContacto;
protected:
	void InitializeGui()
	{
		this->ID=L"AddContacto";
		this->Title=L"AddContacto";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"AddContacto.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceAddContacto.ID=L"serviceAddContacto";
		this->serviceAddContacto.Text=L"AddContacto";
		this->AddChild(serviceAddContacto);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
