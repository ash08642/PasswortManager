#pragma once

#include <wx/wx.h>
#include <vector>
#include <map>

#include "AccountPanel.h"
#include "MasterAccount.h"
#include "MainAddEditAccount.h"
#include "MainViewAccount.h"
#include "CustomButton.h"
#include "NewAccountDialog.h"
#include "SignInDialog.h"
#include "MoreInfoDialog.h"
#include "SearchBar.h"
#include "BackgroundPanel.h"
#include "SVGPanel.h"
#include "AppSetting.h"
#include "HttpClient.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, AppSetting* app_Setting, HttpClient* http_cleint, MasterAccount* master_account);
	~MainFrame();

private:

	AppSetting* appSetting;
	HttpClient* httpCleint;

	std::vector<AccountPanel*> AccountPanels;
	MasterAccount* masterAccount;

	wxPanel* control_panel;
	wxPanel* accounts_panel;

	BackgroundPanel* backgroundPanel2;

	CustomButton* sign_out;
	CustomButton* info;

	SearchBar* searchBar;

	CustomButton* add_new_account;

	MainAddEditAccount* mainAddEditAccount = nullptr;
	MainViewAccount* mainViewAccount = nullptr;

	wxSizer* main_sizer;
	wxSizer* accounts_sizer;
	wxSizer* secondary_controlsizer;
	wxSizer* window_sizer;

	wxFont labelFont;

	void generateButtons();
	void resetWindow();

	void Button_signOut(wxMouseEvent& event);
	void Button_moreInfo(wxMouseEvent& event);
	void Button_addNewAccount(wxMouseEvent& event);
	void Button_MainAddAccount_Confirm(wxMouseEvent& event);
	void Button_MainAddAccount_Cancel(wxMouseEvent& event);
	void Button_MainEditAccount_Confirm(wxMouseEvent& event);
	void Button_MainEditAccount_Cancel(wxMouseEvent& event);
	void Button_MainViewAccount_Edit(wxMouseEvent& event);
	void Button_MainViewAccount_Delete(wxMouseEvent& event);
	void Button_AccountPanel(wxMouseEvent& event);
	void Button_AccountPanel2(wxMouseEvent& event);
	void Button_barSVG(wxMouseEvent& event);
	void Button_searchSVG(wxMouseEvent& event);

	void updateUI_signIn();
	void updateUI_addNewAccount();
	void updateUI_MainAddAccount_Confirm();
	void updateUI_MainAddAccount_Cancel();
	void updateUI_MainEditAccount_Confirm_Cancel(AccountPanel* account_panel);
	void updateUI_MainViewAccount_Edit(AccountPanel* account_panel);
	void updateUI_MainViewAccount_Delete();
	void updateUI_AccountPanel(AccountPanel* account_panel);

	void onSearchBoxChange(wxCommandEvent& event);
};


