#pragma once

#include <wx/wx.h>

#include "TextBox.h"

class NewAccountDialog : public wxDialog
{
public:
    NewAccountDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    virtual ~NewAccountDialog();

    wxString getUsername();
    wxString getPassword();

private:
    wxString username;
    wxString password;
    TextBox* usernameBox = nullptr;
    TextBox* passwordBox = nullptr;
    TextBox* confirmPasswordBox = nullptr;

    void onUpdateOkButton(wxUpdateUIEvent& event);

    virtual bool TransferDataToWindow() override;   // Called when Dialog is created
    virtual bool TransferDataFromWindow() override; // Called when affirmitive event is occured(Ok Button)

    DECLARE_EVENT_TABLE();
};

