#include "stdafx.h"  //________________________________________ ClientWhatsup.cpp
#include "ClientWhatsup.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ClientWhatsup app;
	return app.BeginDialog(IDI_ClientWhatsup, hInstance);
}

void ClientWhatsup::Window_Open(Win::Event& e)
{
	Login login;
	if (!login.BeginDialog(hWnd))
	{
		Destroy();
	}

	password = login.getPassword();
	name = login.GetName();
	phone = login.getUsername();
	userx_id = login.get_id();
	
	//________________________________________________________ lvContactList
	soapContactList.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapContactList.ActionName = L"ContactList";
	soapContactList.AddParameter(L"phone", phone);
	soapContactList.AddParameter(L"Password", password);
	//_________________________________________________________
	soapMessageList.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapMessageList.ActionName = L"MessageList";
	soapMessageList.AddParameter(L"userx_id", userx_id);
	soapMessageList.AddParameter(L"passwordx", password);
	//_________________________________________________________
	soapSendMessage.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapSendMessage.ActionName = L"SendMessage";
	soapSendMessage.AddParameter(L"user_id", userx_id);
	soapSendMessage.AddParameter(L"password", password);
	soapSendMessage.AddParameter(L"recipient_id", userx_id);
	soapSendMessage.AddParameter(L"content", tbxSendMessage.Text);
	//_________________________________________________________
	soapDeleteMessage.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapDeleteMessage.ActionName = L"DeleteMessage";
	soapDeleteMessage.AddParameter(L"userx_id", userx_id);
	soapDeleteMessage.AddParameter(L"password", password);
	soapDeleteMessage.AddParameter(L"message_id",-1);
	UpdateList();
	contact_id = lvContactList.Items[0].Data;
	lbNameContact.Text = lvContactList.Items[0][0].Text;
	lvContactList.Items[0].Selected = true;
	UpdateMessageList();
	//________________________________________________________ lvMessageList
	//________________________________________________________ lvContactMessage
}


void ClientWhatsup::PrepareHttpRequest(Web::HttpRequest& httpRequest, Sys::SoapEnvelope& soap)
{
	httpRequest.Create(soap);
	httpRequest.method = L"POST";
	httpRequest.resource = L"/Whatsup/Whatsup.dll";
}


void ClientWhatsup::UpdateList()
{
	soapContactList.SetParameterValue(L"phone", phone);
	soapContactList.SetParameterValue(L"Password", password);
	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest,soapContactList);

	httpRequest.GetTextToBeSent(text);

	Sys::Socket socket;
	int result = socket.Connect(L"localhost", 80);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	result = socket.Send(httpRequest);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	if (result == SOCKET_DISCONNECTED)
	{
		MessageBox(L"Connection terminate", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	socket.ShutdownSend();
	Web::HttpResponse httpResponse;
	result = socket.Receive(httpResponse);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	Sys::SoapEnvelope soapResult;
	const WCHAR* error = soapResult.CreateFromUtf8(httpResponse.body);
	if (error != NULL)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	httpResponse.GetText(text);
	list<Sys::Xml>::iterator response;
	if (soapResult.GetResponse(response) == false)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	lvContactList.Delete();
	lvContactList.SetRedraw(false);
	lvContactList.ImportFromXml(true, *response);
	lvContactList.SetRedraw(true);
}
void ClientWhatsup::lvContactList_Click(Win::Event& e)
{
	LPARAM Index = lvContactList.GetSelectedIndex();
	if (Index < 0)return;
	contact_id = lvContactList.Items[Index].Data;
	lbNameContact.Text = lvContactList.Items[Index][0].Text;
	UpdateContactMessage();
}



void ClientWhatsup::UpdateMessageList()
{
	soapMessageList.SetParameterValue(L"userx_id", userx_id);
	soapMessageList.SetParameterValue(L"passwordx", password);

	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest, soapMessageList);

	httpRequest.GetTextToBeSent(text);

	Sys::Socket socket;
	int result = socket.Connect(L"localhost", 80);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	result = socket.Send(httpRequest);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	if (result == SOCKET_DISCONNECTED)
	{
		MessageBox(L"Connection terminate", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	socket.ShutdownSend();
	Web::HttpResponse httpResponse;
	result = socket.Receive(httpResponse);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	Sys::SoapEnvelope soapResult;
	const WCHAR* error = soapResult.CreateFromUtf8(httpResponse.body);
	if (error != NULL)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	httpResponse.GetText(text);
	list<Sys::Xml>::iterator response;
	if (soapResult.GetResponse(response) == false)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	lvMessageList.Delete();
	lvMessageList.SetRedraw(false);
	lvMessageList.ImportFromXml(true, *response);
	UpdateContactMessage();
	lvMessageList.SetRedraw(true);
}



void ClientWhatsup::UpdateContactMessage()
{
	int sender_id = 1, senderx_id = -1;
	wstring aux;
	int respient_id = 2, respientx_id = -1,k=0;
	lvContactMessage.SetRedraw(false);
	lvContactMessage.Delete();
	lvContactMessage.Cols.Add(0, LVCFMT_LEFT, 100, L"Enviado");
	lvContactMessage.Cols.Add(1, LVCFMT_RIGHT, 300, L"Mensajes");
	LPARAM Index = lvContactList.GetSelectedIndex();
	for (int i = 0; i < lvMessageList.ItemCount; i++)
	{

		aux = lvMessageList.Items[i][sender_id].GetText();
		if (aux.empty())
		{
			return;
		}
		senderx_id = stoi(aux);
		aux = lvMessageList.Items[i][respient_id].GetText();
		if (aux.empty())
		{
			return;
		}
		respientx_id = stoi(aux);
		if ((senderx_id == contact_id || respientx_id == contact_id))
		{

			lvContactMessage.Items.Add(lvMessageList.Items[i].Data, senderx_id == contact_id ? lvContactList.Items[Index][0].Text : name);
			lvContactMessage.Items[k][1].Text = lvMessageList.Items[i][respient_id+1].Text;
			lvContactMessage.Items[k].Data = lvMessageList.Items[i].Data;
			k++;
		}
	}
	lvContactMessage.SetRedraw(true);
}
void ClientWhatsup::tbxSendMessage_Change(Win::Event& e)
{
}

void ClientWhatsup::btEnviar_Click(Win::Event& e)
{
	SendMessageX();
}

void ClientWhatsup::SendMessageX()
{
	soapSendMessage.SetParameterValue(L"user_id", userx_id);
	soapSendMessage.SetParameterValue(L"password", password);
	soapSendMessage.SetParameterValue(L"recipient_id", contact_id);
	soapSendMessage.SetParameterValue(L"content", tbxSendMessage.Text);

	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest,soapSendMessage);

	httpRequest.GetTextToBeSent(text);

	Sys::Socket socket;
	int result = socket.Connect(L"localhost", 80);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	result = socket.Send(httpRequest);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	if (result == SOCKET_DISCONNECTED)
	{
		MessageBox(L"Connection terminate", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	socket.ShutdownSend();
	Web::HttpResponse httpResponse;
	result = socket.Receive(httpResponse);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	Sys::SoapEnvelope soapResult;
	const WCHAR* error = soapResult.CreateFromUtf8(httpResponse.body);
	if (error != NULL)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	httpResponse.GetText(text);
	list<Sys::Xml>::iterator response;
	if (soapResult.GetResponse(response) == false)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	wstring isSend;
	response->GetChildValue(L"Envidado", isSend);
	if (isSend.compare(L"Yes")==0)
	{
		UpdateMessageList();
		tbxSendMessage.Text=L"";
	}
	else
	{
		tbxSendMessage.ShowBalloonTip(L"ClientWhatsup", L"Mensaje no enviado\n",TTI_ERROR);
	}
}
void ClientWhatsup::btUdate_Click(Win::Event& e)
{
	UpdateMessageList();
}

void ClientWhatsup::btAgregarContacto_Click(Win::Event& e)
{
	AddContacto dlg;
	dlg.password = password;
	dlg.phone = phone;
	if (dlg.BeginDialog(hWnd))
	{
		UpdateList();
	}
}

void ClientWhatsup::btDeleteMs_Click(Win::Event& e)
{
	LPARAM ms_id;
	if (!lvContactMessage.GetSelectedData(ms_id))return;
	soapDeleteMessage.SetParameterValue(L"message_id",ms_id);

	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest, soapDeleteMessage);

	httpRequest.GetTextToBeSent(text);

	Sys::Socket socket;
	int result = socket.Connect(L"localhost", 80);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	result = socket.Send(httpRequest);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}
	if (result == SOCKET_DISCONNECTED)
	{
		MessageBox(L"Connection terminate", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	socket.ShutdownSend();
	Web::HttpResponse httpResponse;
	result = socket.Receive(httpResponse);
	if (result == SOCKET_ERROR)
	{
		MessageBox(L"ClientWhatsup", socket.GetLastErrorDesc(), MB_OK | MB_ICONERROR);
		return;
	}

	Sys::SoapEnvelope soapResult;
	const WCHAR* error = soapResult.CreateFromUtf8(httpResponse.body);
	if (error != NULL)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	httpResponse.GetText(text);
	list<Sys::Xml>::iterator response;
	if (soapResult.GetResponse(response) == false)
	{
		MessageBox(error, L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
	wstring isSend;
	response->GetChildValue(L"DELETE", isSend);
	if (isSend.compare(L"Yes") == 0)
	{
		UpdateMessageList();
		tbxSendMessage.Text = L"";
	}
	else
	{
		tbxSendMessage.ShowBalloonTip(L"ClientWhatsup", L"Mensaje no eliminado\n", TTI_ERROR);
	}
}

