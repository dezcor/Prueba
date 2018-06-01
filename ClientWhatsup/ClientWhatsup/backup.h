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
	Win::Button btUdate;
	Win::Button btAgregarContacto;
	Win::Label lbNameContact;
	Win::Button btDeleteMs;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(22.46313);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(12.80583);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ClientWhatsup";
		lvContactList.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 0.10583, 1.58750, 7.35542, 9.31333, hWnd, 1000);
		lvMessageList.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 11.19188, 0.07938, 11.08604, 10.82146, hWnd, 1001);
		lvContactMessage.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | LVS_ALIGNLEFT | LVS_REPORT, 7.54062, 0.07938, 14.73729, 10.82146, hWnd, 1002);
		tbxSendMessage.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_LEFT | ES_WINNORMALCASE, 0.13229, 10.98021, 16.77458, 1.64042, hWnd, 1003);
		btEnviar.CreateX(NULL, L"Send", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 17.22437, 11.24479, 4.49792, 0.68792, hWnd, 1004);
		btUdate.CreateX(NULL, L"Update Message", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 0.10583, 0.10583, 2.91042, 0.68792, hWnd, 1005);
		btAgregarContacto.CreateX(NULL, L"AddContacto", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 0.13229, 0.84667, 2.88396, 0.68792, hWnd, 1006);
		lbNameContact.CreateX(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 3.28083, 0.13229, 4.15396, 0.60854, hWnd, 1007);
		btDeleteMs.CreateX(NULL, L"Delete Mensaje", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 3.22792, 0.82021, 4.23333, 0.68792, hWnd, 1008);
		lvContactList.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvMessageList.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvContactMessage.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btEnviar);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		lvContactList.Font = fontArial009A;
		lvMessageList.Font = fontArial009A;
		lvContactMessage.Font = fontArial009A;
		tbxSendMessage.Font = fontArial009A;
		btEnviar.Font = fontArial009A;
		btUdate.Font = fontArial009A;
		btAgregarContacto.Font = fontArial009A;
		lbNameContact.Font = fontArial009A;
		btDeleteMs.Font = fontArial009A;
	}
	//_________________________________________________
	void lvContactList_Click(Win::Event& e);
	void tbxSendMessage_Change(Win::Event& e);
	void btEnviar_Click(Win::Event& e);
	void btUdate_Click(Win::Event& e);
	void btAgregarContacto_Click(Win::Event& e);
	void btDeleteMs_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvContactList.IsEvent(e, NM_CLICK)) {lvContactList_Click(e); return true;}
		if (tbxSendMessage.IsEvent(e, EN_CHANGE)) {tbxSendMessage_Change(e); return true;}
		if (btEnviar.IsEvent(e, BN_CLICKED)) {btEnviar_Click(e); return true;}
		if (btUdate.IsEvent(e, BN_CLICKED)) {btUdate_Click(e); return true;}
		if (btAgregarContacto.IsEvent(e, BN_CLICKED)) {btAgregarContacto_Click(e); return true;}
		if (btDeleteMs.IsEvent(e, BN_CLICKED)) {btDeleteMs_Click(e); return true;}
		return false;
	}
};
