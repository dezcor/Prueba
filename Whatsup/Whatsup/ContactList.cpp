#include "stdafx.h"  //_____________________________________________ ContactList.cpp
#include "ContactList.h"

//#include "ContactList.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=ContactList
void ContactList::Window_Open(Web::HttpConnector& h)
{
	serviceContactList.soapEnvelope.ActionXmlns = L"http://www.ugto.com/Whatsup";
	wstring phone = serviceContactList.GetStringParameter(h, L"phone");
	wstring password = serviceContactList.GetStringParameter(h, L"Password");
	serviceContactList.Text = L"ContactList";
	list<Sys::Xml>::iterator response;
	if (!serviceContactList.soapEnvelope.GetResponse(response))return;

	Sys::Xml& userx = response->AddChild(L"userx");
	userx.AddChild(L"userx_id");
	userx.AddChild(L"namex");
	userx.AddChild(L"phone");
	if (password.empty())
		password = L" ";
	if (phone.empty())
		phone = L" ";

	Sql::SqlConnection conn;
	int count;
	try
	{
		wstring select = L"SELECT us.userx_id,namex,phone FROM userx us,contact c WHERE us.userx_id = c.contact_id ";
		select += L"and c.userx_id in";
		select += L"(";
		select += L"SELECT userx_id FROM userx WHERE phone ='"+ phone + L"' and passwordx ='" + password + L"' )";
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		count = conn.ExecuteSelect(select, 100, serviceContactList.soapEnvelope);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

}


