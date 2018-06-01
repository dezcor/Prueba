#include "stdafx.h"  //_____________________________________________ AddContacto.cpp
#include "AddContacto.h"

void AddContacto::Window_Open(Win::Event& e)
{
	soapAddContactList.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapAddContactList.ActionName = L"AddContacto";
	soapAddContactList.AddParameter(L"phone", phone);
	soapAddContactList.AddParameter(L"Password", password);
	soapAddContactList.AddParameter(L"Contact_phone", L"");
}



void AddContacto::btAdd_Click(Win::Event& e)
{
	soapAddContactList.SetParameterValue(L"Contact_phone", tbxPhone.Text);

	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest, soapAddContactList);

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
	response->GetChildValue(L"AddContact", isSend);
	if (isSend.compare(L"YES") == 0)
	{
		EndDialog(true);
	}
	else
	{
		MessageBox(L"No se puede agregar", L"ClientWhatsup", MB_OK | MB_ICONERROR);
		return;
	}
}

void AddContacto::PrepareHttpRequest(Web::HttpRequest& httpRequest, Sys::SoapEnvelope& soap)
{
	httpRequest.Create(soap);
	httpRequest.method = L"POST";
	httpRequest.resource = L"/Whatsup/Whatsup.dll";
}
void AddContacto::btCancel_Click(Win::Event& e)
{
	EndDialog(false);
}

