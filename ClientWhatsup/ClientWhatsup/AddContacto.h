#pragma once   //_____________________________________________ AddContacto.h  
#include "resource.h"

class AddContacto: public Win::Dialog
{
public:
	AddContacto()
	{
	}
	~AddContacto()
	{
	}
	wstring password;
	wstring phone;
	Sys::SoapEnvelope soapAddContactList;
	void PrepareHttpRequest(Web::HttpRequest& httpRequest, Sys::SoapEnvelope& soap);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lb1;
	Win::Textbox tbxPhone;
	Win::Button btAdd;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(8.38729);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(2.03729);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lb1.CreateX(NULL, L"Phone", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.13229, 0.23813, 5.37104, 0.60854, hWnd, 1000);
		tbxPhone.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 0.13229, 0.97896, 5.39750, 0.87313, hWnd, 1001);
		btAdd.CreateX(NULL, L"Add", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 5.74146, 0.18521, 2.46062, 0.68792, hWnd, 1002);
		btCancel.CreateX(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 5.74146, 1.08479, 2.46062, 0.68792, hWnd, 1003);
		this->SetDefaultButton(btAdd);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		lb1.Font = fontArial009A;
		tbxPhone.Font = fontArial009A;
		btAdd.Font = fontArial009A;
		btCancel.Font = fontArial009A;
	}
	//_________________________________________________
	void btAdd_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btAdd.IsEvent(e, BN_CLICKED)) {btAdd_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
