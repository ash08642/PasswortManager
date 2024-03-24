#pragma once

#include <wx/wx.h>

#include "CustomButton.h"
#include "TextBox.h"
#include "SVGPanel.h"
#include "wxImagePanel.h"
#include "AppSetting.h"

class SignInPanel : public wxWindow
{
public:
public:
	SignInPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AppSetting* appSetting);

	wxStaticText* get_signInButton();
	wxStaticText* get_goCreateAccountButton();

	wxString get_identtity();
	wxString get_pass();

private:
	TextBox* identityBox = nullptr;
	TextBox* passwordBox = nullptr;
	TextBox* shownPasswordBox = nullptr;

	SVGPanel* openEyeSVG;
	SVGPanel* closeEyeSVG;

	CustomButton* signInButton;
	CustomButton* dontHaveAnAccount;

	wxSizer* passwordSizer;

	void onPasswordBoxChange(wxCommandEvent& event);
	void onShownPasswordBoxChange(wxCommandEvent& event);

	void showPassword(wxMouseEvent& event);
	void hidePassword(wxMouseEvent& event);
};

