#pragma once   //_____________________________________________ ContactList.h  
#include "resource.h"

class ContactList : public Web::Page
{
public:
	ContactList()
	{
	}
	~ContactList()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceContactList;
protected:
	void InitializeGui()
	{
		this->ID=L"ContactList";
		this->Title=L"ContactList";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"ContactList.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceContactList.ID=L"serviceContactList";
		this->serviceContactList.Text=L"ContactList";
		this->AddChild(serviceContactList);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
