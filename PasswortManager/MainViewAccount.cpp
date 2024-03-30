#include "MainViewAccount.h"

MainViewAccount::MainViewAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AccountPanel* account_panel, AppSetting* app_Setting)
	:wxWindow(parent, id, pos, size), accountPanel{ account_panel }
{
	appSetting = app_Setting;
	this->SetBackgroundColour(*appSetting->order21);

	wxFont labelFont(wxFontInfo(14).FaceName("Dosis").Bold());
	labelFont.SetUnderlined(true);
	wxFont textFont(wxFontInfo(13).FaceName("Dosis-Light"));

	wxStaticText* platformLabel = new wxStaticText(this, wxID_ANY, "Platform / URL: ");
	platformLabel->SetFont(labelFont);
	platformLabel->SetForegroundColour(wxColor(0, 0, 0));
	wxStaticText* platform = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_platform());
	platform->SetFont(textFont);
	platform->SetForegroundColour(wxColor(0, 0, 0));

	wxStaticText* identityLabel = new wxStaticText(this, wxID_ANY, "Identifier: ");
	identityLabel->SetFont(labelFont);
	identityLabel->SetForegroundColour(wxColor(0, 0, 0));
	wxStaticText* identity = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_identifier());
	identity->SetFont(textFont);
	identity->SetForegroundColour(wxColor(0, 0, 0));

	wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, "Password: ");
	passwordLabel->SetFont(labelFont);
	passwordLabel->SetForegroundColour(wxColor(0, 0, 0));
	wxStaticText* password = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_password());
	password->SetFont(textFont);
	password->SetForegroundColour(wxColor(0, 0, 0));

	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(platformLabel, 0, wxLEFT | wxTOP, 20);
	mainSizer->Add(platform, 0, wxLEFT, 25);
	mainSizer->Add(identityLabel, 0, wxLEFT, 20);
	mainSizer->Add(identity, 0, wxLEFT, 25);
	mainSizer->Add(passwordLabel, 0, wxLEFT, 20);
	mainSizer->Add(password, 0, wxLEFT, 25);

	if (accountPanel->get_account()->get_createdAt() == accountPanel->get_account()->get_updated_At())
	{
		wxStaticText* createdAtLabel = new wxStaticText(this, wxID_ANY, "Created At: ");
		createdAtLabel->SetFont(labelFont);
		createdAtLabel->SetForegroundColour(wxColor(0, 0, 0));
		wxStaticText* createdAt = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_createdAt());
		createdAt->SetFont(textFont);
		createdAt->SetForegroundColour(wxColor(0, 0, 0));

		mainSizer->Add(createdAtLabel, 0, wxLEFT, 20);
		mainSizer->Add(createdAt, 0, wxLEFT, 25);
	}
	else
	{
		wxStaticText* createdAtLabel = new wxStaticText(this, wxID_ANY, "Created At: ");
		createdAtLabel->SetFont(labelFont);
		createdAtLabel->SetForegroundColour(wxColor(0, 0, 0));
		wxStaticText* createdAt = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_createdAt());
		createdAt->SetFont(textFont);
		createdAt->SetForegroundColour(wxColor(0, 0, 0));

		wxSizer* createdSizer = new wxBoxSizer(wxVERTICAL);
		createdSizer->Add(createdAtLabel, 0);
		createdSizer->Add(createdAt, 0);

		wxStaticText* updatedAtLabel = new wxStaticText(this, wxID_ANY, "Updated At: ");
		updatedAtLabel->SetFont(labelFont);
		updatedAtLabel->SetForegroundColour(wxColor(0, 0, 0));
		wxStaticText* updatedAt = new wxStaticText(this, wxID_ANY, accountPanel->get_account()->get_updated_At());
		updatedAt->SetFont(textFont);
		updatedAt->SetForegroundColour(wxColor(0, 0, 0));

		wxSizer* updatedSizer = new wxBoxSizer(wxVERTICAL);
		updatedSizer->Add(updatedAtLabel, 0);
		updatedSizer->Add(updatedAt, 0);

		wxSizer* timeSizer = new wxBoxSizer(wxVERTICAL);
		timeSizer->Add(createdSizer, 0);
		timeSizer->Add(updatedSizer, 0);
		mainSizer->Add(timeSizer, 0, wxLEFT, 20);
	}

	//Edit = new CustomButton(this, wxSize(90, 30), wxColor(141, 247, 221), "Edit");
	Edit = new CustomButton(this, wxSize(100, 30), *appSetting->order6, *appSetting->order61, appSetting->selected_language[AppSetting::TextKeys::Edit], true, textFont, *appSetting->order3, false);
	//Delete = new CustomButton(this, wxSize(90, 30), wxColor(189, 102, 91), "Delete");
	Delete = new CustomButton(this, wxSize(100, 30), *appSetting->order6, *appSetting->order61, appSetting->selected_language[AppSetting::TextKeys::Delete], true, textFont, *appSetting->order3, false);

	wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(Edit, 2, wxALIGN_CENTRE);
	buttonSizer->AddSpacer(45);
	buttonSizer->Add(Delete, 2, wxALIGN_CENTRE);
	mainSizer->AddStretchSpacer(1);
	mainSizer->Add(buttonSizer, 0, wxBOTTOM | wxLEFT, 15);
	SetSizer(mainSizer);
	//SetMinSize(wxSize(300, 600));
	//Fit();
}

wxStaticText* MainViewAccount::get_EditButton()
{
	return Edit->getClickablePanel();
}
wxStaticText* MainViewAccount::get_DeleteButton()
{
	return Delete->getClickablePanel();
}

AccountPanel* MainViewAccount::get_accountPanel()
{
	return accountPanel;
}