#pragma once

#include <wx/wx.h>
#include "RedisterationFrame.h"
#include "MainFrame.h"
#include "HttpClient.h"

class PasswordManagerApp : public wxApp
{
public:
	virtual bool OnInit();
	~PasswordManagerApp();

private:
	AppSetting* appSetting;
	MasterAccount* masterAccount;
	HttpClient* httpCleint;
	RedisterationFrame* redisterationFrame;
	MainFrame* mainFrame;

	void display_Mainframe_signIn(wxMouseEvent& event);
	void display_Mainframe_signUp(wxMouseEvent& event);
};

