#pragma once   //_____________________________________________ Login.h  
#include "resource.h"

class Login : public Win::Dialog
{
public:
	Login()
	{
	}
	~Login()
	{
	}
	wstring& getUsername();
	wstring& getPassword();
	wstring& GetName();
	int get_id();
	Sys::SoapEnvelope soapLogin;
	void PrepareHttpRequest(Web::HttpRequest& httpRequest);
	void isTermino(int i);
private:
	int userx_id;
	wstring name;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lb1;
	Win::Label lb2;
	Win::Textbox tbxUsername;
	Win::Textbox tbxPassword;
	Win::Button btOK;
	Win::Button btCancel;
	Win::Button btNewUser;
	Win::Textbox tbxName;
	Win::Label lb3;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(10.95375);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(3.09563);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lb1.CreateX(NULL, L"Phone", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.23813, 0.34396, 3.14854, 0.60854, hWnd, 1000);
		lb2.CreateX(NULL, L"Password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.21167, 1.32292, 3.20146, 0.60854, hWnd, 1001);
		tbxUsername.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 3.73062, 0.34396, 4.18042, 0.60854, hWnd, 1002);
		tbxPassword.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 3.73062, 1.34937, 4.18042, 0.60854, hWnd, 1003);
		btOK.CreateX(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 8.49313, 0.31750, 2.24896, 0.68792, hWnd, 1004);
		btCancel.CreateX(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 8.46667, 1.32292, 2.27542, 0.68792, hWnd, 1005);
		btNewUser.CreateX(NULL, L"New User", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 8.49313, 2.14312, 2.27542, 0.68792, hWnd, 1006);
		tbxName.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 3.73062, 2.24896, 4.18042, 0.60854, hWnd, 1007);
		lb3.CreateX(NULL, L"Name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.23813, 2.30187, 3.22792, 0.60854, hWnd, 1008);
		this->SetDefaultButton(btOK);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		lb1.Font = fontArial009A;
		lb2.Font = fontArial009A;
		tbxUsername.Font = fontArial009A;
		tbxPassword.Font = fontArial009A;
		btOK.Font = fontArial009A;
		btCancel.Font = fontArial009A;
		btNewUser.Font = fontArial009A;
		tbxName.Font = fontArial009A;
		lb3.Font = fontArial009A;
	}
	//_________________________________________________
	void tbxUsername_Change(Win::Event& e);
	void tbxPassword_Change(Win::Event& e);
	void btOK_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void btNewUser_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (tbxUsername.IsEvent(e, EN_CHANGE)) {tbxUsername_Change(e); return true;}
		if (tbxPassword.IsEvent(e, EN_CHANGE)) {tbxPassword_Change(e); return true;}
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		if (btNewUser.IsEvent(e, BN_CLICKED)) {btNewUser_Click(e); return true;}
		return false;
	}
};


