#include "PasswordManagerApp.h"

bool PasswordManagerApp::OnInit()
{
	appSetting = new AppSetting();
	masterAccount = new MasterAccount();
	httpCleint = new HttpClient("localhost", 1234);

	redisterationFrame = new RedisterationFrame("Password Manager", wxDefaultPosition, wxSize(900,600), appSetting, masterAccount, httpCleint);
	redisterationFrame->Show(true);
	redisterationFrame->get_signInButton()->Bind(wxEVT_LEFT_DOWN, &PasswordManagerApp::display_Mainframe_signIn, this);
	redisterationFrame->get_signUpButton()->Bind(wxEVT_LEFT_DOWN, &PasswordManagerApp::display_Mainframe_signUp, this);
	return true;
}

PasswordManagerApp::~PasswordManagerApp()
{
	delete appSetting;
	delete masterAccount;
	delete httpCleint;
}

void PasswordManagerApp::display_Mainframe_signIn(wxMouseEvent& event)
{
	if (redisterationFrame->validate_signInData())
	{
		wxMessageBox("signIn Succesesful");
		redisterationFrame->clear_fields();
		mainFrame = new MainFrame("Password Manager", wxDefaultPosition, wxDefaultSize, appSetting, httpCleint, masterAccount);
		redisterationFrame->Show(false);
		mainFrame->Show(true);
	}
	else
	{
		wxMessageBox("signIn failed");
	}
}
void PasswordManagerApp::display_Mainframe_signUp(wxMouseEvent& event)
{
	if (redisterationFrame->validate_signUpData())
	{
		wxMessageBox("signUp Succesesful");
		redisterationFrame->clear_fields();
		mainFrame = new MainFrame("Password Manager", wxDefaultPosition, wxDefaultSize, appSetting, httpCleint, masterAccount);
		redisterationFrame->Show(false);
		mainFrame->Show(true);
	}
	else
	{
		wxMessageBox("signUp failed");
	}
}
