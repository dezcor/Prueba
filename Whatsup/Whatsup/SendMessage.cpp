#include "stdafx.h"  //_____________________________________________ SendMessage.cpp
#include "SendMessage.h"

//#include "SendMessage.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=SendMessage
void SendMessagex::Window_Open(Web::HttpConnector& h)
{
	serviceSendMessage.soapEnvelope.ActionXmlns = L"http://www.ugto.com/WhatsApp";
	const int userx_id = serviceSendMessage.GetIntParameter(h, L"user_id");
	wstring password = serviceSendMessage.GetStringParameter(h, L"password");
	const int contact_id = serviceSendMessage.GetIntParameter(h, L"recipient_id");
	wstring content = serviceSendMessage.GetStringParameter(h, L"content");
	serviceSendMessage.Text = L"SendMessage";
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
		Sys::Format(cmd, L"SELECT count(*) FROM userx WHERE userx_id = %d AND passwordx = '%s'", userx_id, password.c_str());
		if (!conn.GetInt(cmd))
		{
			serviceSendMessage.soapEnvelope.AddParameter(L"Envidado", L"NO");
			return;
		}

		Sys::Format(cmd, L"SELECT count(*) FROM contact WHERE userx_id = %d AND contact_id = %d", userx_id, contact_id);
		if (!conn.GetInt(cmd))
		{
			serviceSendMessage.soapEnvelope.AddParameter(L"Envidado", L"NO");
			return;
		}
		Sys::Format(cmd, L"INSERT INTO messagex (submited_date, sender_id,recipient_id,content,is_sent,is_read) VALUES(GETDATE(),%d,%d,'%s',1,0)", userx_id, contact_id, content.c_str());
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of inserted rows", MB_OK | MB_ICONERROR);
			serviceSendMessage.soapEnvelope.AddParameter(L"Envidado", L"NO");
		}
		else serviceSendMessage.soapEnvelope.AddParameter(L"Envidado", L"Yes");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		serviceSendMessage.soapEnvelope.AddParameter(L"Envidado", L"NO");
	}


}


