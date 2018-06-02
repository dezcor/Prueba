#pragma once  //______________________________________ ClientWhatsup.h  
#include "Resource.h"
#include "Login.h"
#include "AddContacto.h"
class ClientWhatsup: public Win::Dialog
{
public:
	ClientWhatsup()
	{
	}
	~ClientWhatsup()
	{
		timer.Kill(1);
	}
private:
	wstring  phone;
	wstring name;
	wstring password;
	int userx_id;
	int contact_id;
	Sys::SoapEnvelope soapContactList;
	Sys::SoapEnvelope soapMessageList;
	Sys::SoapEnvelope soapSendMessage;
	Sys::SoapEnvelope soapDeleteMessage;
	void UpdateList();
	void UpdateMessageList();
	void SendMessageX();
	void UpdateContactMessage();
	void PrepareHttpRequest(Web::HttpRequest& httpRequest, Sys::SoapEnvelope& soap);
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::ListView lvContactList;
	Win::ListView lvMessageList;
	Win::ListView lvContactMessage;
	Win::Textbox tbxSendMessage;
	Win::Button btEnviar;
	Win::Button btAgregarContacto;
	Win::Label lbNameContact;
	Win::Button btDeleteMs;
	Win::Label lbPhone;
protected:
	Win::Gdi::Font fontArial009A;
	Win::Gdi::Font fontInk_Free009A;
	Win::Gdi::Font fontInk_Free009B;
	Win::Gdi::Font fontInk_Free009D;
	Win::Gdi::Font fontInk_Free014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(20.18771);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(12.80583);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ClientWhatsup";
		lvContactList.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 0.10583, 1.58750, 6.74688, 9.31333, hWnd, 1000);
		lvMessageList.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 11.19188, 0.07938, 8.81062, 10.82146, hWnd, 1001);
		lvContactMessage.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 6.85271, 0.07938, 13.14979, 10.82146, hWnd, 1002);
		tbxSendMessage.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_LEFT | ES_WINNORMALCASE, 0.10583, 10.90083, 16.80104, 1.71979, hWnd, 1003);
		btEnviar.CreateX(NULL, L"Send", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 17.22437, 11.24479, 2.75167, 0.68792, hWnd, 1004);
		btAgregarContacto.CreateX(NULL, L"AddContacto", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 0.07938, 0.84667, 3.46604, 0.68792, hWnd, 1005);
		lbNameContact.CreateX(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 3.65125, 0.10583, 3.20146, 0.68792, hWnd, 1006);
		btDeleteMs.CreateX(NULL, L"Delete Mensaje", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 0.07938, 0.13229, 3.41313, 0.68792, hWnd, 1007);
		lbPhone.CreateX(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 3.67771, 0.87313, 3.17500, 0.60854, hWnd, 1008);
		lvContactList.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvMessageList.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvContactMessage.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btEnviar);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		fontInk_Free009A.CreateX(L"Ink Free", 0.317500, false, false, false, false);
		fontInk_Free009B.CreateX(L"Ink Free", 0.317500, false, true, false, false);
		fontInk_Free009D.CreateX(L"Ink Free", 0.317500, true, true, false, false);
		fontInk_Free014A.CreateX(L"Ink Free", 0.493889, false, false, false, false);
		lvContactList.Font = fontInk_Free009B;
		lvMessageList.Font = fontArial009A;
		lvContactMessage.Font = fontInk_Free009A;
		tbxSendMessage.Font = fontArial009A;
		btEnviar.Font = fontArial009A;
		btAgregarContacto.Font = fontInk_Free009D;
		lbNameContact.Font = fontInk_Free014A;
		btDeleteMs.Font = fontInk_Free009D;
		lbPhone.Font = fontInk_Free009A;
	}
	//_________________________________________________
	void lvContactList_Click(Win::Event& e);
	void tbxSendMessage_Change(Win::Event& e);
	void btEnviar_Click(Win::Event& e);
	void btAgregarContacto_Click(Win::Event& e);
	void btDeleteMs_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Window_Timer(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvContactList.IsEvent(e, NM_CLICK)) {lvContactList_Click(e); return true;}
		if (tbxSendMessage.IsEvent(e, EN_CHANGE)) {tbxSendMessage_Change(e); return true;}
		if (btEnviar.IsEvent(e, BN_CLICKED)) {btEnviar_Click(e); return true;}
		if (btAgregarContacto.IsEvent(e, BN_CLICKED)) {btAgregarContacto_Click(e); return true;}
		if (btDeleteMs.IsEvent(e, BN_CLICKED)) {btDeleteMs_Click(e); return true;}
		return false;
	}
};
