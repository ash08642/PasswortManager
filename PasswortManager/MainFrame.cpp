#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, AppSetting* app_Setting, HttpClient* http_cleint, MasterAccount* master_account) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
 
	appSetting = app_Setting;
	httpCleint = http_cleint;
	masterAccount = master_account;

	wxIcon app_icon;

	wxImage::AddHandler(new wxPNGHandler);
	app_icon.LoadFile("Images/beautiful_flat-style_logo_desi.png", wxBITMAP_TYPE_PNG);

	if (app_icon.IsOk()) {
		SetIcon(app_icon);
	}
	else
	{
		wxMessageBox("App icon failed");
	}
	if (!wxFont::AddPrivateFont("Fonts/Dosis-Bold.ttf"))
	{
		wxMessageBox("Dosis-Bold Failed to load");
	}
	if (!wxFont::AddPrivateFont("Fonts/Dosis-Light.ttf"))
	{
		wxMessageBox("Dosis-Light Failed to load");
	}

	labelFont = wxFont(wxFontInfo(14).FaceName("Dosis").Bold());

	//masterAccount = new MasterAccount{};
	this->SetBackgroundColour(wxColor(0, 0, 0));

	wxSizer* control_sizer = new wxBoxSizer(wxVERTICAL);
	control_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(70, 850));
	control_panel->SetBackgroundColour(wxColor(54, 100, 117));

	accounts_sizer = new wxBoxSizer(wxVERTICAL);
	accounts_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 850));
	accounts_panel->SetBackgroundColour(wxColor(18, 33, 38));

	window_sizer = new wxBoxSizer(wxVERTICAL);

	backgroundPanel2 = new BackgroundPanel(this, wxSize(350, 500), "Images/darkbg.png", wxBITMAP_TYPE_PNG);

	generateButtons();
	secondary_controlsizer = new wxBoxSizer(wxVERTICAL);
	secondary_controlsizer->Add(sign_out, 0, wxALIGN_CENTRE_HORIZONTAL, 0);
	control_sizer->Add(secondary_controlsizer, 0, wxEXPAND | wxALL, 0);
	control_sizer->AddStretchSpacer(1);
	control_sizer->Add(info, 0, wxALIGN_TOP | wxEXPAND, 0);

	accounts_sizer->Add(searchBar, 0, wxEXPAND, 0);

	//window_sizer->Add(backgroundPanel, 1, wxEXPAND, 0);
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);

	control_panel->SetSizerAndFit(control_sizer);
	accounts_panel->SetSizerAndFit(accounts_sizer);
	backgroundPanel2->SetSizer(window_sizer);

	main_sizer = new wxBoxSizer(wxHORIZONTAL);
	main_sizer->Add(control_panel, 0, wxEXPAND, 1);
	main_sizer->Add(accounts_panel, 0, wxEXPAND | wxLEFT, 1);
	main_sizer->Add(backgroundPanel2, 1, wxEXPAND | wxLEFT, 1);

	this->SetSizerAndFit(main_sizer);

	sign_out->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_signOut, this);
	info->getClickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_moreInfo, this);
	add_new_account->getClickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_addNewAccount, this);
	searchBar->get_barSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_barSVG, this);
	searchBar->get_searchSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_searchSVG, this);
	searchBar->get_searchBar()->Bind(wxEVT_TEXT, &MainFrame::onSearchBoxChange, this);

	AccountPanels = AccountPanel::FillFromDB(masterAccount->get_username(), httpCleint, masterAccount->get_key(), accounts_panel, AccountPanels);
	updateUI_signIn();
}

void MainFrame::generateButtons()
{
	/*sign_up = new CustomButton(control_panel, wxSize(70, 70), wxColor(141, 247, 221), "Sign", "Up");
	sign_in = new CustomButton(control_panel, wxSize(70, 70), wxColor(141, 247, 221), "Sign", "In");
	sign_out = new CustomButton(control_panel, wxSize(70, 70), wxColor(141, 247, 221), "Sign", "Out");
	info = new CustomButton(control_panel, wxSize(70, 70), wxColor(141, 247, 221), "More", "Info");*/

	sign_out = new CustomButton(control_panel, wxSize(70, 70), wxColor(141, 247, 221), "Sign", "Out");
	info = new CustomButton(control_panel, wxSize(70, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::MoreInfo], true, labelFont, *appSetting->order3, false);

	searchBar = new SearchBar(accounts_panel, wxSize(250, 30));

	//backgroundPanel = new BackgroundPanel(backgroundPanel2, wxSize(300, 400), "Images/theme2.png", wxBITMAP_TYPE_PNG);
	//add_new_account = new CustomButton(backgroundPanel2, wxSize(200, 40), wxColor(141, 247, 221), "+ Add New Account");
	add_new_account = new CustomButton(backgroundPanel2, wxSize(100, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::AddNewAccount], true, labelFont, *appSetting->order3, false);
}
void MainFrame::resetWindow()
{
	if (mainAddEditAccount != nullptr)
	{
		window_sizer->Detach(mainAddEditAccount);
		delete mainAddEditAccount;
		mainAddEditAccount = nullptr;
	}
	if (mainViewAccount != nullptr)
	{
		window_sizer->Detach(mainViewAccount);
		delete mainViewAccount;
		mainViewAccount = nullptr;
	}
	/*if (backgroundPanel->IsShown())
	{
		backgroundPanel->Hide();
	}*/
	window_sizer->Detach(add_new_account);
	add_new_account->Hide();
	for (size_t i = 0; i < window_sizer->GetItemCount(); i++)
	{
		window_sizer->Detach(i);
	}
}

//void MainFrame::Button_signIn(wxMouseEvent& event)
//{
//	SignInDialog* signInDialog = new SignInDialog(this, wxID_ANY, "Sign In");
//	if (signInDialog->ShowModal() == wxID_OK)
//	{
//		if (masterAccount->Login(signInDialog->getUsername(), signInDialog->getPassword()))
//		{
//			AccountPanels = AccountPanel::ReadFromFile(
//				masterAccount->get_id(),
//				masterAccount->get_password(),
//				accounts_panel,
//				AccountPanels
//			);
//			add_new_account->getClickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_addNewAccount, this);
//			searchBar->reset();
//			searchBar->get_barSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_barSVG, this);
//			searchBar->get_searchSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_searchSVG, this);
//			searchBar->get_searchBar()->Bind(wxEVT_TEXT, &MainFrame::onSearchBoxChange, this);
//			updateUI_signIn();
//		}
//	}
//	signInDialog->Destroy();
//}
//void MainFrame::Button_signUp(wxMouseEvent& event)
//{
//	NewAccountDialog* newAccountDialog = new NewAccountDialog(this, wxID_ANY, "Sign Up a New Account");
//	if (newAccountDialog->ShowModal() == wxID_OK)
//	{
//		if (masterAccount->CreateNewMasterAccount(newAccountDialog->getUsername(), newAccountDialog->getPassword()))
//		{
//			updateUI_signUp();
//			add_new_account->getClickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_addNewAccount, this);
//			searchBar->reset();
//			searchBar->get_barSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_barSVG, this);
//			searchBar->get_searchSVG()->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_searchSVG, this);
//			searchBar->get_searchBar()->Bind(wxEVT_TEXT, &MainFrame::onSearchBoxChange, this);
//		}
//	}
//	newAccountDialog->Destroy();
//}
void MainFrame::Button_signOut(wxMouseEvent& event)
{
	masterAccount->SignOut();
	//updateUI_signOut();
	add_new_account->getClickablePanel()->Unbind(wxEVT_LEFT_DOWN, &MainFrame::Button_addNewAccount, this);
	searchBar->get_barSVG()->get_clickablePanel()->Unbind(wxEVT_LEFT_DOWN, &MainFrame::Button_barSVG, this);
	searchBar->get_searchSVG()->get_clickablePanel()->Unbind(wxEVT_LEFT_DOWN, &MainFrame::Button_searchSVG, this);
	searchBar->get_searchBar()->Unbind(wxEVT_TEXT, &MainFrame::onSearchBoxChange, this);
	searchBar->reset();
}
void MainFrame::Button_moreInfo(wxMouseEvent& event)
{
	MoreInfoDialog* moreInfoDialog = new MoreInfoDialog(this);
	if (moreInfoDialog->ShowModal() == wxID_OK)
	{
		moreInfoDialog->Destroy();
	}
}

void MainFrame::Button_addNewAccount(wxMouseEvent& event)
{
	updateUI_addNewAccount();
	mainAddEditAccount->get_ConfirmButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainAddAccount_Confirm, this);
	mainAddEditAccount->get_CancelButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainAddAccount_Cancel, this);

}
void MainFrame::Button_MainAddAccount_Confirm(wxMouseEvent& event)
{
	if (!mainAddEditAccount->isFilled())
	{
		wxMessageBox("Please fill all fields");
		return;
	}
	Account* newAccount = new Account(
		masterAccount->get_username(),
		mainAddEditAccount->get_platform(),
		mainAddEditAccount->get_identity(),
		mainAddEditAccount->get_password(),
		masterAccount->get_key()
	);
	newAccount->AddToDB(httpCleint);//
	AccountPanels.push_back(new AccountPanel(accounts_panel, wxID_ANY, wxDefaultPosition, wxSize(250, 50), AccountPanels.size(), AccountPanels, newAccount));
	AccountPanels[AccountPanels.size() - 1]->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel, this);
	AccountPanels[AccountPanels.size() - 1]->get_clickable_platformBitmap()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel2, this);
	AccountPanels[AccountPanels.size() - 1]->get_clickable_identifierBitmap()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel2, this);
	updateUI_MainAddAccount_Confirm();
}
void MainFrame::Button_MainAddAccount_Cancel(wxMouseEvent& event)
{
	updateUI_MainAddAccount_Cancel();
}
void MainFrame::Button_MainEditAccount_Confirm(wxMouseEvent& event)
{
	if (mainAddEditAccount->isFilled())
	{
		mainAddEditAccount->get_accountPanel()->update_account(
			mainAddEditAccount->get_platform(),
			mainAddEditAccount->get_identity(),
			mainAddEditAccount->get_password(),
			masterAccount->get_key(),
			mainAddEditAccount->get_accountPanel()->get_account()->get_password()
		);
		mainAddEditAccount->get_accountPanel()->get_account()->UpdateInDB(httpCleint);//
		mainAddEditAccount->get_accountPanel()->Refresh();
		updateUI_MainEditAccount_Confirm_Cancel(mainAddEditAccount->get_accountPanel());
	}
	else
	{
		wxMessageBox("Please Fill All Fields");
	}
}
void MainFrame::Button_MainEditAccount_Cancel(wxMouseEvent& event)
{
	updateUI_MainEditAccount_Confirm_Cancel(mainAddEditAccount->get_accountPanel());
}
void MainFrame::Button_MainViewAccount_Edit(wxMouseEvent& event)
{
	updateUI_MainViewAccount_Edit(mainViewAccount->get_accountPanel());
}
void MainFrame::Button_MainViewAccount_Delete(wxMouseEvent& event)
{
	mainViewAccount->get_accountPanel()->reset();
	accounts_sizer->Detach(mainViewAccount->get_accountPanel());
	mainViewAccount->get_accountPanel()->get_account()->DeleteFromDB(httpCleint);//
	mainViewAccount->get_accountPanel()->changeContainerBeforeDeleting();
	updateUI_MainViewAccount_Delete();
}
void MainFrame::Button_AccountPanel(wxMouseEvent& event)
{
	AccountPanel* accountPanel = (AccountPanel*)event.GetEventObject();
	if (!accountPanel->is_selected())
	{
		accountPanel->OnMouseDown();
		updateUI_AccountPanel(accountPanel);
	}
}
void MainFrame::Button_AccountPanel2(wxMouseEvent& event)
{
	//wxMessageBox("svg clicked");
	wxStaticBitmap* pic = (wxStaticBitmap*)event.GetEventObject();
	SVGPanel* svgPanel = (SVGPanel*)pic->GetParent();
	AccountPanel* accountPanel = (AccountPanel*)svgPanel->GetParent();
	if (!accountPanel->is_selected())
	{
		accountPanel->OnMouseDown();
		updateUI_AccountPanel(accountPanel);
	}
}
void MainFrame::Button_barSVG(wxMouseEvent& event)
{
	if (control_panel->IsShown())
	{
		control_panel->Hide();
	}
	else
	{
		control_panel->Show();
	}
	Layout();
}
void MainFrame::Button_searchSVG(wxMouseEvent& event)
{
	if (!searchBar->get_searchBar()->IsEmpty())
	{
		for (int i = 0; i < AccountPanels.size(); i++)
		{
			if (
				(AccountPanels[i]->get_account()->get_platform().Contains(searchBar->get_searchBar()->GetValue())) ||
				(AccountPanels[i]->get_account()->get_identifier().Contains(searchBar->get_searchBar()->GetValue())))
			{
				accounts_sizer->Show(AccountPanels[i], true);
				Layout();
			}
			else
			{
				accounts_sizer->Show(AccountPanels[i], false);
				Layout();
			}
		}
	}
}

void MainFrame::onSearchBoxChange(wxCommandEvent& event)
{
	if (searchBar->get_searchBar()->IsEmpty())
	{
		accounts_sizer->ShowItems(true);
		Layout();
	}
}

//void MainFrame::updateUI_signUp()
//{
//	secondary_controlsizer->Show(sign_up, false);
//	secondary_controlsizer->Show(sign_in, false);
//	secondary_controlsizer->Show(sign_out, true);
//	if (control_panel->IsShown())
//	{
//		control_panel->Hide();
//	}
//	Layout();
//}
void MainFrame::updateUI_signIn()
{
	for (int i = 0; i < AccountPanels.size(); i++)
	{
		accounts_sizer->Add(AccountPanels[i], 0, wxEXPAND | wxTOP, 1);
		AccountPanels[i]->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel, this);
		AccountPanels[i]->get_clickable_identifierBitmap()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel2, this);
		AccountPanels[i]->get_clickable_platformBitmap()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_AccountPanel2, this);
	}
	Layout();
}
//void MainFrame::updateUI_signOut()
//{
//	secondary_controlsizer->Show(sign_up, true);
//	secondary_controlsizer->Show(sign_in, true);
//	secondary_controlsizer->Show(sign_out, false);
//	for (int i = 0; i < AccountPanels.size(); i++)
//	{
//		accounts_sizer->Detach(AccountPanels[i]);
//		delete AccountPanels[i];
//	}
//	AccountPanels.resize(0);
//	resetWindow();
//	//backgroundPanel->Show();
//	window_sizer->AddStretchSpacer(1);
//	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
//	add_new_account->Show();
//	if (!control_panel->IsShown())
//	{
//		control_panel->Show();
//	}
//	Layout();
//}
void MainFrame::updateUI_addNewAccount()
{
	resetWindow();
	if (AccountPanels.size() > 0)
	{
		AccountPanel::resetAll(AccountPanels);
	}
	mainAddEditAccount = new MainAddEditAccount(backgroundPanel2, wxID_ANY, wxDefaultPosition, wxSize(300, 400), appSetting);
	window_sizer->Add(mainAddEditAccount, 0, wxALIGN_CENTRE | wxTOP, 30);
	Layout();
}
void MainFrame::updateUI_MainAddAccount_Confirm()
{
	//wxMessageBox("Account Created");
	accounts_sizer->Add(AccountPanels[AccountPanels.size() - 1], 0, wxEXPAND | wxTOP, 1);
	resetWindow();
	//backgroundPanel->Show();
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}
void MainFrame::updateUI_MainAddAccount_Cancel()
{
	//wxMessageBox("Cancelled Account Creation");
	resetWindow();
	//backgroundPanel->Show();
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}
void MainFrame::updateUI_MainEditAccount_Confirm_Cancel(AccountPanel* account_panel)
{
	resetWindow();
	mainViewAccount = new MainViewAccount(backgroundPanel2, wxID_ANY, wxDefaultPosition, wxSize(300, 400), account_panel, appSetting);
	mainViewAccount->get_EditButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainViewAccount_Edit, this);
	mainViewAccount->get_DeleteButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainViewAccount_Delete, this);
	window_sizer->Add(mainViewAccount, 0, wxALIGN_CENTRE | wxTOP, 25);
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}
void MainFrame::updateUI_MainViewAccount_Edit(AccountPanel* account_panel)
{
	resetWindow();
	mainAddEditAccount = new MainAddEditAccount(backgroundPanel2, wxID_ANY, wxDefaultPosition, wxSize(300, 400), account_panel, appSetting);
	window_sizer->Add(mainAddEditAccount, 0, wxALIGN_CENTRE | wxTOP, 25);
	mainAddEditAccount->get_ConfirmButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainEditAccount_Confirm, this);
	mainAddEditAccount->get_CancelButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainEditAccount_Cancel, this);
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}
void MainFrame::updateUI_MainViewAccount_Delete()
{
	resetWindow();
	//backgroundPanel->Show();
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}
void MainFrame::updateUI_AccountPanel(AccountPanel* account_panel)
{
	resetWindow();
	mainViewAccount = new MainViewAccount(backgroundPanel2, wxID_ANY, wxDefaultPosition, wxSize(300, 400), account_panel, appSetting);
	mainViewAccount->get_EditButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainViewAccount_Edit, this);
	mainViewAccount->get_DeleteButton()->Bind(wxEVT_LEFT_DOWN, &MainFrame::Button_MainViewAccount_Delete, this);
	window_sizer->Add(mainViewAccount, 0, wxALIGN_CENTRE | wxTOP, 25);
	window_sizer->AddStretchSpacer(1);
	window_sizer->Add(add_new_account, 0, wxEXPAND, 0);
	add_new_account->Show();
	Layout();
}

MainFrame::~MainFrame()
{
	//delete masterAccount;
}