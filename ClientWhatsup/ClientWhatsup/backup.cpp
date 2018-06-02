#include "stdafx.h"  //_____________________________________________ Login.cpp
#include "Login.h"

void Login::Window_Open(Win::Event& e)
{
	soapLogin.ActionXmlns = L"http://www.ugto.com/Whatsup";
	soapLogin.ActionName = L"Login";
	soapLogin.AddParameter(L"name", L" ");
	soapLogin.AddParameter(L"phone", L" ");
	soapLogin.AddParameter(L"password", L" ");
	lb3.Visible = false;
	tbxName.Visible = false;
}

void Login::btOK_Click(Win::Event& e)
{
	soapLogin.ActionName = L"Login";
	Win::BusyCursor cursor(true);
	wstring text;
	static int i = 0;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest);
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
	wstring user_id;
	list<Sys::Xml>::iterator isOK;
	response->GetChild(L"userx",isOK);
	if (!isOK->GetChildValue(L"userx_id", user_id))
	{
		isTermino(++i);
		return;
	}
	if (!isOK->GetChildValue(L"namex", name))
	{
		isTermino(++i);
		return;
	}
	wstring phone;
	if (!isOK->GetChildValue(L"phone", phone))
	{
		isTermino(++i);
		return;
	}
	if (user_id.empty())
	{
		isTermino(++i);
		return;
	}
	userx_id = stoi(user_id);
	if (tbxUsername.Text.compare(phone) == 0)
		EndDialog(true);
	else
		isTermino(++i);
}

void Login::btCancel_Click(Win::Event& e)
{
	EndDialog(false);
}

wstring& Login::getPassword()
{
	return tbxPassword.Text;
}

wstring& Login::getUsername()
{
	return tbxUsername.Text;
}


void Login::tbxUsername_Change(Win::Event& e)
{
	soapLogin.SetParameterValue(L"phone", tbxUsername.Text);
}

void Login::tbxPassword_Change(Win::Event& e)
{
	soapLogin.SetParameterValue(L"password", tbxPassword.Text);
}

wstring& Login::GetName()
{
	return name;
}

int Login::get_id()
{
	return userx_id;
}


void Login::PrepareHttpRequest(Web::HttpRequest& httpRequest)
{
	httpRequest.Create(soapLogin);
	httpRequest.method = L"POST";
	httpRequest.resource = L"/Whatsup/Whatsup.dll";
}


void Login::isTermino(int i)
{
	if (i >= 3)
		EndDialog(false);
}

void Login::btNewUser_Click(Win::Event& e)
{
	if (lb3.Visible == false)
	{
		lb3.Visible = true;
		tbxName.Visible = true;
		tbxUsername.ShowBalloonTip(L"ClientWhatsup", L"Place the phone, password and name\nAnd click again from New User", TTI_INFO);
		return;
	}
	if (tbxName.Text.empty())
	{
		tbxName.ShowBalloonTip(L"ClientWhatsup", L"put name please", TTI_INFO);
	}
	if (tbxPassword.Text.length() < 4)
	{
		tbxName.ShowBalloonTip(L"ClientWhatsup", L"please enter the password more than 4 characters", TTI_INFO);
	}
	soapLogin.ActionName = L"NewUser";
	soapLogin.SetParameterValue(L"name", tbxName.Text);
	Win::BusyCursor cursor(true);
	wstring text;
	Web::HttpRequest httpRequest;
	PrepareHttpRequest(httpRequest);

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
	wstring isAdd;
	response->GetChildValue(L"Add", isAdd);
	if (isAdd.compare(L"Yes") == 0)
		tbxUsername.ShowBalloonTip(L"ClientWhatsup", L"Press ok", TTI_INFO);
	else
		tbxUsername.ShowBalloonTip(L"ClientWhatsup", L"Invaluable phone", TTI_INFO);
}

