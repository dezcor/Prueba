#include "stdafx.h"  //_____________________________________________ MessageList.cpp
#include "MessageList.h"

//#include "MessageList.h" //<< ADD THIS LINE IN THE Whatsup.cpp FILE

// http://localhost/Whatsup.dll?windowID=MessageList
void MessageList::Window_Open(Web::HttpConnector& h)
{
	serviceMessageList.soapEnvelope.ActionXmlns = L"http://www.ugto.com/WhatsApp";
	const int userx_id = serviceMessageList.GetIntParameter(h, L"userx_id");
	const wstring password = serviceMessageList.GetStringParameter(h, L"passwordx");
	serviceMessageList.Text = L"MessageList";

	list<Sys::Xml>::iterator response;
	if (!serviceMessageList.soapEnvelope.GetResponse(response))return;

	Sys::Xml& userx = response->AddChild(L"Send");
	userx.AddChild(L"message_id");
	userx.AddChild(L"submited_date");
	userx.AddChild(L"sender_id");
	userx.AddChild(L"recipient_id");
	userx.AddChild(L"content");
	userx.AddChild(L"is_sent");
	userx.AddChild(L"is_read");
	/**********************************************************
	*
	*
	*SLECT lista de Mensaje
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
			return;
		}
		/****************************************************/


		Sys::Format(cmd, L"SELECT message_id, submited_date, sender_id, recipient_id, content, is_sent,is_read FROM messagex WHERE sender_id = %d OR recipient_id = %d", userx_id, userx_id);
		conn.ExecuteSelect(cmd, 100, serviceMessageList.soapEnvelope);
		/************************************************
		*************************************************/
		//Sys::Xml& contact = response->AddChild(L"Recibido");
		//contact.AddChild(L"message_id");
		//contact.AddChild(L"submited_date");
		//contact.AddChild(L"sender_id");
		//contact.AddChild(L"namex");
		//contact.AddChild(L"content");
		//contact.AddChild(L"is_read");

		//Sys::Format(cmd, L"SELECT message_id, submited_date, sender_id, namex,content, is_read FROM userx, messagex WHERE recipient_id = %d AND sender_id = userx_id", userx_id);
		//conn.ExecuteSelect(cmd, 100, serviceMessageList.soapEnvelope);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

	/*serviceMessageList.soapEnvelope.AddParameter(L"result", x+y);*/
}



