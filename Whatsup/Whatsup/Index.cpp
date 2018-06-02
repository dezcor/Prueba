#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
}

void Index::btContactList_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"ContactList");
}

void Index::btSendMessage_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"SendMessage");
}

void Index::btMessageList_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"MessageList");
}

void Index::btDeleteMessage_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"DeleteMessage");
}

void Index::btNewUser_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"NewUser");
}

void Index::btAddContacto_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"AddContacto");
}

void Index::btLogin_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"Login");
}

