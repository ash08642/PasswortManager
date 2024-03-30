#include "SignInPanel.h"

SignInPanel::SignInPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AppSetting* appSetting)
    :wxWindow(parent, id, pos, size)
{
    this->SetBackgroundColour(*appSetting->order2);

    wxFont labelFont(wxFontInfo(14).FaceName("Dosis-Light"));
    //labelFont.SetUnderlined(true);
    wxFont textFont(wxFontInfo(13).FaceName("Dosis-Light"));

    wxImagePanel* drawPane = new wxImagePanel(this, wxT("Images/beautiful_flat-style_logo_desi.png"), wxBITMAP_TYPE_PNG, wxSize(90, 90));

    wxSizer* identitySizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* identityLabel = new wxStaticText(this, wxID_ANY, appSetting->selected_language[AppSetting::TextKeys::Username] + "/" + appSetting->selected_language[AppSetting::TextKeys::Email]);
    identityLabel->SetFont(labelFont);
    //identityLabel->SetForegroundColour(wxColor(177, 231, 250));
    identitySizer->Add(identityLabel);
    identityBox = new TextBox(this, wxEmptyString, wxSize(294, 34), 0, *appSetting->order6, *appSetting->order61, *appSetting->order1, *appSetting->order3, textFont);
    identitySizer->Add(identityBox, 0);

    passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, appSetting->selected_language[AppSetting::TextKeys::Password]);
    passwordLabel->SetFont(labelFont);
    //passwordLabel->SetForegroundColour(wxColor(177, 231, 250));
    passwordSizer->Add(passwordLabel);
    passwordBox = new TextBox(this, wxEmptyString, wxSize(264, 34), wxTE_PASSWORD | wxTE_PROCESS_ENTER, *appSetting->order6, *appSetting->order61, *appSetting->order1, *appSetting->order3, textFont);
    wxString closeEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M3.98 8.223A10.477 10.477 0 0 0 1.934 12C3.226 16.338 7.244 19.5 12 19.5c.993 0 1.953-.138 2.863-.395M6.228 6.228A10.451 10.451 0 0 1 12 4.5c4.756 0 8.773 3.162 10.065 7.498a10.522 10.522 0 0 1-4.293 5.774M6.228 6.228 3 3m3.228 3.228 3.65 3.65m7.894 7.894L21 21m-3.228-3.228-3.65-3.65m0 0a3 3 0 1 0-4.243-4.243m4.242 4.242L9.88 9.88" /></svg>)");
    openEyeSVG = new SVGPanel(this, wxSize(34, 34), closeEyeString, *appSetting->order6, *appSetting->order61);
    wxSizer* hiddenPassSizer = new wxBoxSizer(wxHORIZONTAL);
    hiddenPassSizer->Add(passwordBox, 0);
    hiddenPassSizer->Add(openEyeSVG, 0);
    passwordSizer->Add(hiddenPassSizer, 0);

    shownPasswordBox = new TextBox(this, wxEmptyString, wxSize(264, 34), wxTE_PROCESS_ENTER, *appSetting->order6, *appSetting->order61, *appSetting->order1, *appSetting->order3, textFont);
    wxString openEyeString(R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M2.036 12.322a1.012 1.012 0 0 1 0-.639C3.423 7.51 7.36 4.5 12 4.5c4.638 0 8.573 3.007 9.963 7.178.07.207.07.431 0 .639C20.577 16.49 16.64 19.5 12 19.5c-4.638 0-8.573-3.007-9.963-7.178Z" /><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 1 1-6 0 3 3 0 0 1 6 0Z" /></svg>)");
    closeEyeSVG = new SVGPanel(this, wxSize(34, 34), openEyeString, *appSetting->order6, *appSetting->order61);
    wxSizer* shownPassSizer = new wxBoxSizer(wxHORIZONTAL);
    shownPassSizer->Add(shownPasswordBox, 0);
    shownPassSizer->Add(closeEyeSVG, 0);
    passwordSizer->Add(shownPassSizer, 0);
    passwordSizer->Hide(2);

    signInButton = new CustomButton(this, wxSize(100, 30), *appSetting->order6, *appSetting->order61, appSetting->selected_language[AppSetting::TextKeys::Login], true, labelFont, *appSetting->order3, false);
    dontHaveAnAccount = new CustomButton(this, wxDefaultSize, this->GetBackgroundColour(), this->GetBackgroundColour(), appSetting->selected_language[AppSetting::TextKeys::DontHaveAnAccount], false, labelFont, *appSetting->order3, true);
    signInButton->SetMaxSize(wxSize(90, 30));
    dontHaveAnAccount->SetMaxSize(wxSize(90, 30));
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(dontHaveAnAccount);
    buttonSizer->AddSpacer(25);
    buttonSizer->Add(signInButton);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(drawPane, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 15);
    mainSizer->Add(identitySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 15);
    mainSizer->Add(passwordSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 15);
    mainSizer->Add(buttonSizer, 1, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 15);
    SetSizer(mainSizer);

    shownPasswordBox->get_textCtrl()->Bind(wxEVT_TEXT, &SignInPanel::onShownPasswordBoxChange, this);
    passwordBox->get_textCtrl()->Bind(wxEVT_TEXT, &SignInPanel::onPasswordBoxChange, this);
    openEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &SignInPanel::showPassword, this);
    closeEyeSVG->get_clickablePanel()->Bind(wxEVT_LEFT_DOWN, &SignInPanel::hidePassword, this);
}

void SignInPanel::onPasswordBoxChange(wxCommandEvent& event)
{
    shownPasswordBox->get_textCtrl()->SetValue(passwordBox->get_textCtrl()->GetValue());
}
void SignInPanel::onShownPasswordBoxChange(wxCommandEvent& event)
{
    passwordBox->get_textCtrl()->SetValue(shownPasswordBox->get_textCtrl()->GetValue());
}

void SignInPanel::showPassword(wxMouseEvent& event)
{
    passwordSizer->Hide(1);
    passwordSizer->Show(2, true);
    Layout();
}
void SignInPanel::hidePassword(wxMouseEvent& event)
{
    passwordSizer->Hide(2);
    passwordSizer->Show(1, true);
    Layout();
}

void SignInPanel::clear_fields()
{
    identityBox->get_textCtrl()->SetValue("");
    passwordBox->get_textCtrl()->ChangeValue("");
    shownPasswordBox->get_textCtrl()->ChangeValue("");
}

wxStaticText* SignInPanel::get_goCreateAccountButton()
{
    return dontHaveAnAccount->getClickablePanel();
}
wxStaticText* SignInPanel::get_signInButton()
{
    return signInButton->getClickablePanel();
}

wxString SignInPanel::get_identtity()
{
    return identityBox->get_textCtrl()->GetValue();
}
wxString SignInPanel::get_pass()
{
    return passwordBox->get_textCtrl()->GetValue();
}
