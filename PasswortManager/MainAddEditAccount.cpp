#include "MainAddEditAccount.h"

MainAddEditAccount::MainAddEditAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AppSetting* app_Setting)
    :wxWindow(parent, id, pos, size)
{
    this->SetBackgroundColour(wxColor(20, 37, 43));

    appSetting = app_Setting;

    wxFont labelFont(wxFontInfo(14).FaceName("Dosis").Bold());
    labelFont.SetUnderlined(true);
    wxFont textFont(wxFontInfo(13).FaceName("Dosis Light").Bold());

    wxSizer* platformSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* platformLabel = new wxStaticText(this, wxID_ANY, "Platform/Url :");
    platformLabel->SetFont(labelFont);
    platformLabel->SetForegroundColour(wxColor(177, 231, 250));
    platformSizer->Add(platformLabel);
    platformBox = new TextBox(this, wxEmptyString, wxSize(254, 34), 0, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    platformSizer->Add(platformBox, 0);

    wxSizer* identitySizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* identityLabel = new wxStaticText(this, wxID_ANY, "Username/email: ");
    identityLabel->SetFont(labelFont);
    identityLabel->SetForegroundColour(wxColor(177, 231, 250));
    identitySizer->Add(identityLabel);
    identityBox = new TextBox(this, wxEmptyString, wxSize(254, 34), 0, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    identitySizer->Add(identityBox, 0);

    passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, "Password: ");
    passwordLabel->SetFont(labelFont);
    passwordLabel->SetForegroundColour(wxColor(177, 231, 250));
    passwordSizer->Add(passwordLabel);
    passwordBox = new TextBox(this, wxEmptyString, wxSize(224, 34), wxTE_PASSWORD | wxTE_PROCESS_ENTER, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    wxString closeEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M3.98 8.223A10.477 10.477 0 0 0 1.934 12C3.226 16.338 7.244 19.5 12 19.5c.993 0 1.953-.138 2.863-.395M6.228 6.228A10.451 10.451 0 0 1 12 4.5c4.756 0 8.773 3.162 10.065 7.498a10.522 10.522 0 0 1-4.293 5.774M6.228 6.228 3 3m3.228 3.228 3.65 3.65m7.894 7.894L21 21m-3.228-3.228-3.65-3.65m0 0a3 3 0 1 0-4.243-4.243m4.242 4.242L9.88 9.88" /></svg>)");
    openEyeSVG = new SVGPanel(this, wxSize(34, 34), closeEyeString, wxColor(75, 140, 163));
    wxSizer* hiddenPassSizer = new wxBoxSizer(wxHORIZONTAL);
    hiddenPassSizer->Add(passwordBox, 0);
    hiddenPassSizer->Add(openEyeSVG, 0);
    passwordSizer->Add(hiddenPassSizer, 0);

    shownPasswordBox = new TextBox(this, wxEmptyString, wxSize(224, 34), wxTE_PROCESS_ENTER, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(187, 243, 255), textFont);
    wxString openEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M2.036 12.322a1.012 1.012 0 0 1 0-.639C3.423 7.51 7.36 4.5 12 4.5c4.638 0 8.573 3.007 9.963 7.178.07.207.07.431 0 .639C20.577 16.49 16.64 19.5 12 19.5c-4.638 0-8.573-3.007-9.963-7.178Z" /><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 1 1-6 0 3 3 0 0 1 6 0Z" /></svg>)");
    closeEyeSVG = new SVGPanel(this, wxSize(34, 34), openEyeString, wxColor(75, 140, 163));
    wxSizer* shownPassSizer = new wxBoxSizer(wxHORIZONTAL);
    shownPassSizer->Add(shownPasswordBox, 0);
    shownPassSizer->Add(closeEyeSVG, 0);
    passwordSizer->Add(shownPassSizer, 0);
    passwordSizer->Hide(2);

    //Confirm = new CustomButton(this, wxSize(90, 30), wxColor(141, 247, 221), "Confirm");
    Confirm = new CustomButton(this, wxSize(100, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::Confirm], true, labelFont, *appSetting->order3, false);
    // Cancel = new CustomButton(this, wxSize(90, 30), wxColor(189, 102, 91), "Cancel");
    Cancel = new CustomButton(this, wxSize(100, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::Cancel], true, labelFont, *appSetting->order3, false);

    Confirm->SetMaxSize(wxSize(90, 30));
    Cancel->SetMaxSize(wxSize(90, 30));
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Confirm, 2, wxALIGN_CENTRE);
    buttonSizer->AddSpacer(45);
    buttonSizer->Add(Cancel, 2, wxALIGN_CENTRE);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(platformSizer, 0, wxTOP | wxLEFT, 15);
    mainSizer->Add(identitySizer, 0, wxBOTTOM | wxLEFT, 15);
    mainSizer->Add(passwordSizer, 0, wxBOTTOM | wxLEFT, 15);
    mainSizer->Add(buttonSizer, 1, wxBOTTOM | wxLEFT, 15);
    SetSizer(mainSizer);

    shownPasswordBox->get_textCtrl()->Bind(wxEVT_TEXT, &MainAddEditAccount::onShownPasswordBoxChange, this);
    passwordBox->get_textCtrl()->Bind(wxEVT_TEXT, &MainAddEditAccount::onPasswordBoxChange, this);
    openEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainAddEditAccount::showPassword, this);
    closeEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainAddEditAccount::hidePassword, this);
}

MainAddEditAccount::MainAddEditAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AccountPanel* account_panel, AppSetting* app_Setting)
    :wxWindow(parent, id, pos, size), accountPanel{ account_panel }
{
    this->SetBackgroundColour(wxColor(20, 37, 43));

    appSetting = app_Setting;
    wxFont labelFont(wxFontInfo(14).FaceName("Dosis").Bold());
    labelFont.SetUnderlined(true);
    wxFont textFont(wxFontInfo(13).FaceName("Dosis Light").Bold());

    wxSizer* platformSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* platformLabel = new wxStaticText(this, wxID_ANY, "Platform/Url :");
    platformLabel->SetFont(labelFont);
    platformLabel->SetForegroundColour(wxColor(177, 231, 250));
    platformSizer->Add(platformLabel);
    platformBox = new TextBox(this, accountPanel->get_account()->get_platform(), wxSize(254, 34), 0, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    platformSizer->Add(platformBox, 0);

    wxSizer* identitySizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* identityLabel = new wxStaticText(this, wxID_ANY, "Username/email: ");
    identityLabel->SetFont(labelFont);
    identityLabel->SetForegroundColour(wxColor(177, 231, 250));
    identitySizer->Add(identityLabel);
    identityBox = new TextBox(this, accountPanel->get_account()->get_identifier(), wxSize(254, 34), 0, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    identitySizer->Add(identityBox, 0);

    passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, "Password: ");
    passwordLabel->SetFont(labelFont);
    passwordLabel->SetForegroundColour(wxColor(177, 231, 250));
    passwordSizer->Add(passwordLabel);
    passwordBox = new TextBox(this, accountPanel->get_account()->get_password(), wxSize(224, 34), wxTE_PASSWORD | wxTE_PROCESS_ENTER, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    wxString closeEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M3.98 8.223A10.477 10.477 0 0 0 1.934 12C3.226 16.338 7.244 19.5 12 19.5c.993 0 1.953-.138 2.863-.395M6.228 6.228A10.451 10.451 0 0 1 12 4.5c4.756 0 8.773 3.162 10.065 7.498a10.522 10.522 0 0 1-4.293 5.774M6.228 6.228 3 3m3.228 3.228 3.65 3.65m7.894 7.894L21 21m-3.228-3.228-3.65-3.65m0 0a3 3 0 1 0-4.243-4.243m4.242 4.242L9.88 9.88" /></svg>)");
    openEyeSVG = new SVGPanel(this, wxSize(34, 34), closeEyeString, wxColor(75, 140, 163));
    wxSizer* hiddenPassSizer = new wxBoxSizer(wxHORIZONTAL);
    hiddenPassSizer->Add(passwordBox, 0);
    hiddenPassSizer->Add(openEyeSVG, 0);
    passwordSizer->Add(hiddenPassSizer, 0);

    shownPasswordBox = new TextBox(this, accountPanel->get_account()->get_password(), wxSize(224, 34), wxTE_PROCESS_ENTER, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(187, 243, 255), textFont);
    wxString openEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M2.036 12.322a1.012 1.012 0 0 1 0-.639C3.423 7.51 7.36 4.5 12 4.5c4.638 0 8.573 3.007 9.963 7.178.07.207.07.431 0 .639C20.577 16.49 16.64 19.5 12 19.5c-4.638 0-8.573-3.007-9.963-7.178Z" /><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 1 1-6 0 3 3 0 0 1 6 0Z" /></svg>)");
    closeEyeSVG = new SVGPanel(this, wxSize(34, 34), openEyeString, wxColor(75, 140, 163));
    wxSizer* shownPassSizer = new wxBoxSizer(wxHORIZONTAL);
    shownPassSizer->Add(shownPasswordBox, 0);
    shownPassSizer->Add(closeEyeSVG, 0);
    passwordSizer->Add(shownPassSizer, 0);
    passwordSizer->Hide(2);

    //Confirm = new CustomButton(this, wxSize(90, 30), wxColor(141, 247, 221), "Confirm");
    Confirm = new CustomButton(this, wxSize(100, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::Confirm], true, labelFont, *appSetting->order3, false);
    //Cancel = new CustomButton(this, wxSize(90, 30), wxColor(189, 102, 91), "Cancel");
    Cancel = new CustomButton(this, wxSize(100, 30), *appSetting->order6, appSetting->selected_language[AppSetting::TextKeys::Cancel], true, labelFont, *appSetting->order3, false);

    Confirm->SetMaxSize(wxSize(90, 30));
    Cancel->SetMaxSize(wxSize(90, 30));
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Confirm, 2, wxALIGN_CENTRE);
    buttonSizer->AddSpacer(45);
    buttonSizer->Add(Cancel, 2, wxALIGN_CENTRE);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(platformSizer, 0, wxTOP | wxLEFT, 15);
    mainSizer->Add(identitySizer, 0, wxBOTTOM | wxLEFT, 15);
    mainSizer->Add(passwordSizer, 0, wxBOTTOM | wxLEFT, 15);
    mainSizer->Add(buttonSizer, 1, wxBOTTOM | wxLEFT, 15);
    SetSizer(mainSizer);

    shownPasswordBox->get_textCtrl()->Bind(wxEVT_TEXT, &MainAddEditAccount::onShownPasswordBoxChange, this);
    passwordBox->get_textCtrl()->Bind(wxEVT_TEXT, &MainAddEditAccount::onPasswordBoxChange, this);
    openEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainAddEditAccount::showPassword, this);
    closeEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &MainAddEditAccount::hidePassword, this);
}

wxString MainAddEditAccount::get_platform()
{
    return platformBox->get_textCtrl()->GetValue();
}
wxString MainAddEditAccount::get_identity()
{
    return identityBox->get_textCtrl()->GetValue();
}
wxString MainAddEditAccount::get_password()
{
    return passwordBox->get_textCtrl()->GetValue();
}

wxStaticText* MainAddEditAccount::get_ConfirmButton()
{
    return Confirm->getClickablePanel();
}
wxStaticText* MainAddEditAccount::get_CancelButton()
{
    return Cancel->getClickablePanel();
}

void MainAddEditAccount::onPasswordBoxChange(wxCommandEvent& event)
{
    shownPasswordBox->get_textCtrl()->SetValue(passwordBox->get_textCtrl()->GetValue());
}
void MainAddEditAccount::onShownPasswordBoxChange(wxCommandEvent& event)
{
    passwordBox->get_textCtrl()->SetValue(shownPasswordBox->get_textCtrl()->GetValue());
}
AccountPanel* MainAddEditAccount::get_accountPanel()
{
    return accountPanel;
}
bool MainAddEditAccount::isFilled()
{
    if (!identityBox->get_textCtrl()->IsEmpty() && !platformBox->get_textCtrl()->IsEmpty() && !passwordBox->get_textCtrl()->IsEmpty())
    {
        return true;
    }
    return false;
}
void MainAddEditAccount::showPassword(wxMouseEvent& event)
{
    passwordSizer->Hide(1);
    passwordSizer->Show(2, true);
    Layout();
}
void MainAddEditAccount::hidePassword(wxMouseEvent& event)
{
    passwordSizer->Hide(2);
    passwordSizer->Show(1, true);
    Layout();
}