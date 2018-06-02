#include "stdafx.h"  //_____________________________________________ NewUser.cpp
#include "NewUser.h"

//#include "NewUser.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=NewUser
void NewUser::Window_Open(Web::HttpConnector& h)
{
	serviceNewUser.soapEnvelope.ActionXmlns = L"http://www.ugto.com/Whastup";
	const wstring name = serviceNewUser.GetStringParameter(h, L"name");
	const wstring phone = serviceNewUser.GetStringParameter(h, L"phone");
	const wstring password = serviceNewUser.GetStringParameter(h, L"password");
	serviceNewUser.Text = L"NewUser";

	std::wregex rphone(L"[0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]");
	if (!regex_match(phone, rphone))
	{
		serviceNewUser.soapEnvelope.AddParameter(L"Add", L"NO");
		return;
	}
	/**********************************************************
	*
	*
	*Insert O Send Mensaje
	***********************************************************/
	Sql::SqlConnection conn;
	wstring cmd;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT count(*) FROM userx WHERE phone = '%s'",phone.c_str() );
		if (conn.GetInt(cmd))
		{
			serviceNewUser.soapEnvelope.AddParameter(L"Add", L"NO");
			return;
		}
		Sys::Format(cmd, L"INSERT INTO  userx (namex,phone,passwordx) VALUES('%s','%s','%s')", name.c_str(), phone.c_str(), password.c_str());
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of inserted rows", MB_OK | MB_ICONERROR);
			serviceNewUser.soapEnvelope.AddParameter(L"Add", L"NO");
		}
		else serviceNewUser.soapEnvelope.AddParameter(L"Add", L"Yes");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		serviceNewUser.soapEnvelope.AddParameter(L"Add", L"NO");
	}
}



