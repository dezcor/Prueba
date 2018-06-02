#include "stdafx.h"  //_____________________________________________ DeleteMessage.cpp
#include "DeleteMessage.h"

//#include "DeleteMessage.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=DeleteMessage
void DeleteMessage::Window_Open(Web::HttpConnector& h)
{
	serviceDeleteMessage.soapEnvelope.ActionXmlns = L"http://www.ugto.com/WhatsApp";
	const int userx_id = serviceDeleteMessage.GetIntParameter(h, L"userx_id");
	const wstring password = serviceDeleteMessage.GetStringParameter(h, L"password");
	const int message_id = serviceDeleteMessage.GetIntParameter(h, L"message_id");

	serviceDeleteMessage.Text = L"DeleteMessage";

	Sql::SqlConnection conn;
	wstring cmd;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"DELETE FROM messagex WHERE message_id=%d", message_id);;
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
			serviceDeleteMessage.soapEnvelope.AddParameter(L"DELETE", L"No");
		}
		else
			serviceDeleteMessage.soapEnvelope.AddParameter(L"DELETE", L"Yes");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		serviceDeleteMessage.soapEnvelope.AddParameter(L"DELETE", L"No");
	}


}


