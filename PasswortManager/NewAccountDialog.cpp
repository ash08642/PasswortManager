#include "NewAccountDialog.h"

BEGIN_EVENT_TABLE(NewAccountDialog, wxDialog)
EVT_UPDATE_UI(wxID_OK, NewAccountDialog::onUpdateOkButton)
END_EVENT_TABLE()

NewAccountDialog::NewAccountDialog(wxWindow* parent,
    wxWindowID id,
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

    wxSizer* confirmPasswordSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* confirmPasswordLabel = new wxStaticText(this, wxID_ANY, "Confirm Password: ");
    confirmPasswordLabel->SetFont(labelFont);
    confirmPasswordLabel->SetForegroundColour(wxColor(177, 231, 250));
    confirmPasswordSizer->Add(confirmPasswordLabel);
    confirmPasswordBox = new TextBox(this, wxEmptyString, wxSize(225, 30), wxTE_PASSWORD, wxColor(35, 65, 75), wxColor(30, 55, 64), wxColor(177, 231, 250), textFont);
    confirmPasswordSizer->Add(confirmPasswordBox);

    //wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    wxButton* Ok = new wxButton(this, wxID_OK, "Sign In", wxDefaultPosition, wxSize(60, 30));
    Ok->SetBackgroundColour(wxColor(141, 247, 221));
    wxButton* Cancel = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(60, 30));
    Cancel->SetBackgroundColour(wxColor(189, 102, 91));
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Ok, 0);
    buttonSizer->Add(Cancel, 0, wxLEFT, 20);

    mainSizer->Add(usernameSizer, 0, wxLEFT | wxTOP | wxRIGHT | wxBOTTOM, 15);
    mainSizer->Add(passwordSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 15);
    mainSizer->Add(confirmPasswordSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 15);
    mainSizer->Add(buttonSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 15);

    SetSizer(mainSizer);
    SetMinSize(wxSize(300, 300));
    Fit();
}

NewAccountDialog::~NewAccountDialog()
{
}

wxString NewAccountDialog::getUsername()
{
    return username;
}

wxString NewAccountDialog::getPassword()
{
    return password;
}

void NewAccountDialog::onUpdateOkButton(wxUpdateUIEvent& event)
{
    event.Enable(false);
    if (!usernameBox->get_textCtrl()->GetValue().empty() && !passwordBox->get_textCtrl()->GetValue().empty() && !confirmPasswordBox->get_textCtrl()->GetValue().empty() && (passwordBox->get_textCtrl()->GetValue() == confirmPasswordBox->get_textCtrl()->GetValue()))
    {
        event.Enable(true);
    }
}

bool NewAccountDialog::TransferDataToWindow()
{
    return true;
}

bool NewAccountDialog::TransferDataFromWindow()
{
    username = usernameBox->get_textCtrl()->GetValue();
    password = passwordBox->get_textCtrl()->GetValue();
    return true;
}