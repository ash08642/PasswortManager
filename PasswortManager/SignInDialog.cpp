#include "SignInDialog.h"

BEGIN_EVENT_TABLE(SignInDialog, wxDialog)
EVT_UPDATE_UI(wxID_OK, SignInDialog::onUpdateOkButton)
END_EVENT_TABLE()

SignInDialog::SignInDialog(wxWindow* parent, wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name) :
    wxDialog(parent, id, title, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(20, 37, 43));

    wxFont labelFont(wxFontInfo(14).FaceName("Dosis").Bold());
    labelFont.SetUnderlined(true);
    wxFont textFont(wxFontInfo(13).FaceName("Dosis Light").Bold());

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxSizer* usernameSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* usernameLabel = new wxStaticText(this, wxID_ANY, "Username: ");
    usernameLabel->SetFont(labelFont);
    usernameLabel->SetForegroundColour(wxColor(177, 231, 250));
    usernameSizer->Add(usernameLabel);
    usernameBox = new TextBox(this, wxEmptyString, wxSize(225, 30), 0, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    usernameSizer->Add(usernameBox);

    wxSizer* passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, "Password: ");
    passwordLabel->SetFont(labelFont);
    passwordLabel->SetForegroundColour(wxColor(177, 231, 250));
    passwordSizer->Add(passwordLabel);
    passwordBox = new TextBox(this, wxEmptyString, wxSize(225, 30), wxTE_PASSWORD, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    passwordSizer->Add(passwordBox);

    //wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    wxButton* Ok = new wxButton(this, wxID_OK, "Sign In", wxDefaultPosition, wxSize(60, 30));
    Ok->SetBackgroundColour(wxColor(141, 247, 221));
    wxButton* Cancel = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(60, 30));
    Cancel->SetBackgroundColour(wxColor(189, 102, 91));
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Ok, 0);
    buttonSizer->Add(Cancel, 0, wxLEFT, 20);

    mainSizer->Add(usernameSizer, 0, wxLEFT | wxTOP | wxBOTTOM, 15);
    mainSizer->Add(passwordSizer, 0, wxLEFT | wxBOTTOM, 15);
    mainSizer->Add(buttonSizer, 0, wxLEFT | wxBOTTOM, 15);

    SetSizer(mainSizer);
    SetMinSize(wxSize(300, 200));
    Fit();
}

void SignInDialog::onUpdateOkButton(wxUpdateUIEvent& event)
{
    event.Enable(false);
    if (!usernameBox->get_textCtrl()->GetValue().empty() && !passwordBox->get_textCtrl()->GetValue().empty())
    {
        event.Enable(true);
    }
}

bool SignInDialog::TransferDataToWindow()
{
    return true;
}

bool SignInDialog::TransferDataFromWindow()
{
    username = usernameBox->get_textCtrl()->GetValue();
    password = passwordBox->get_textCtrl()->GetValue();
    return true;
}

wxString SignInDialog::getUsername()
{
    return username;
}

wxString SignInDialog::getPassword()
{
    return password;
}