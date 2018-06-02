#include "stdafx.h"  //_____________________________________________ AddContacto.cpp
#include "AddContacto.h"

//#include "AddContacto.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=AddContacto
void AddContacto::Window_Open(Web::HttpConnector& h)
{
	serviceAddContacto.soapEnvelope.ActionXmlns = L"http://www.ugto.com/Whatsup";
	const wstring phone = serviceAddContacto.GetStringParameter(h, L"phone");
	const wstring password = serviceAddContacto.GetStringParameter(h, L"Password");
	const wstring Contactphone = serviceAddContacto.GetStringParameter(h, L"Contact_phone");
	serviceAddContacto.Text = L"AddContacto";

	Sql::SqlConnection conn;
	wstring cmd;
	int rows = 0;
	int contact_id;
	int userx_id;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT sum(userx_id) FROM userx WHERE phone = '%s' AND passwordx = '%s'",phone.c_str(), password.c_str());
		userx_id=conn.GetInt(cmd);
		if (!userx_id)
		{
			serviceAddContacto.soapEnvelope.AddParameter(L"AddContact", L"NO");
			return;
		}

		Sys::Format(cmd, L"SELECT sum(userx_id) FROM userx WHERE phone = '%s'", Contactphone.c_str());
		contact_id = conn.GetInt(cmd);
		if (!contact_id)
		{
			serviceAddContacto.soapEnvelope.AddParameter(L"AddContact", L"NO");
			return;
		}
		Sys::Format(cmd, L"INSERT INTO contact(userx_id,contact_id) VALUES(%d,%d)", userx_id, contact_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of inserted rows", MB_OK | MB_ICONERROR);
			serviceAddContacto.soapEnvelope.AddParameter(L"AddContact", L"NO");
		}
		else serviceAddContacto.soapEnvelope.AddParameter(L"AddContact", L"YES");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		serviceAddContacto.soapEnvelope.AddParameter(L"AddContact", L"NO");
	}
}



