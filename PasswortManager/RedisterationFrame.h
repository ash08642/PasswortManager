#pragma once

#include <wx/wx.h>
#include "SignUpPanel.h"
#include "SignInPanel.h"
#include "AppSetting.h"
#include "MasterAccount.h"
#include "HttpClient.h"
#include "Crypto.h"

class RedisterationFrame : public wxFrame
{
private:
	AppSetting* appSetting;
	MasterAccount* masterAccount;
	HttpClient* httpCleint;

	wxStaticText* signInButton;
	wxStaticText* signUpButton;

	wxImage image;
	wxBitmap resized;
	int w, h;

	SignInPanel* signInPanel;
	SignUpPanel* signUpPanel;

	wxSizer* sizer;

	void showSignIn(wxMouseEvent& event);
	void showSignUp(wxMouseEvent& event);
public:
	RedisterationFrame(const wxString& title, const wxPoint& pos, const wxSize& size, AppSetting* settings, MasterAccount* mas_acc, HttpClient* client);

	wxStaticText* get_signInButton();
	wxStaticText* get_signUpButton();

	
	bool validate_signUpData();	//gibt true zurück, wenn signUp erfolgreich war
	bool validate_signInData();	//gibt true zurück, wenn signIn erfolgreich war

	void clear_fields();

	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void render(wxDC& dc);

	DECLARE_EVENT_TABLE()
};

