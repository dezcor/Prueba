#include "stdafx.h"  //_____________________________________________ Login.cpp
#include "Login.h"

//#include "Login.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=Login
void Login::Window_Open(Web::HttpConnector& h)
{
	serviceLogin.soapEnvelope.ActionXmlns = L"http://www.ugto.com/Whatsup";
	const wstring phone = serviceLogin.GetStringParameter(h, L"phone");
	const wstring password = serviceLogin.GetStringParameter(h, L"password");
	serviceLogin.Text = L"Login";
	list<Sys::Xml>::iterator response;
	if (!serviceLogin.soapEnvelope.GetResponse(response))return;

	Sys::Xml& userx = response->AddChild(L"userx");
	userx.AddChild(L"userx_id");
	userx.AddChild(L"namex");
	userx.AddChild(L"phone");

	Sql::SqlConnection conn;
	wstring cmd;
	int count = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT userx_id, namex, phone FROM userx WHERE phone = '%s' AND passwordx = '%s'",phone.c_str(), password.c_str());
		count = conn.ExecuteSelect(cmd, 100, serviceLogin.soapEnvelope);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}



