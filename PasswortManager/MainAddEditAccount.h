#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <vector>
#include "MasterAccount.h"
#include "AccountPanel.h"
#include "CustomButton.h"
#include "TextBox.h"
#include "SVGPanel.h"
#include "AppSetting.h"

class MainAddEditAccount : public wxWindow
{
public:
	MainAddEditAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AppSetting* app_Setting);
	MainAddEditAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AccountPanel* account_panel, AppSetting* app_Setting);

	wxString get_platform();
	wxString get_identity();
	wxString get_password();

	wxStaticText* get_ConfirmButton();
	wxStaticText* get_CancelButton();

	AccountPanel* get_accountPanel();
	bool isFilled();
private:
	TextBox* platformBox = nullptr;
	TextBox* identityBox = nullptr;
	TextBox* passwordBox = nullptr;
	TextBox* shownPasswordBox = nullptr;

	SVGPanel* openEyeSVG;
	SVGPanel* closeEyeSVG;

	CustomButton* Confirm;
	CustomButton* Cancel;
	CustomButton* GeneratePasssword;

	AccountPanel* accountPanel;

	wxSizer* passwordSizer;

	AppSetting* appSetting;

	void onPasswordBoxChange(wxCommandEvent& event);
	void onShownPasswordBoxChange(wxCommandEvent& event);

	void showPassword(wxMouseEvent& event);
	void hidePassword(wxMouseEvent& event);

	/*Diese Funktion erzeugt eine zufällige Zeichenfolge der Länge 14, 
	die stark genug ist, um auf den meisten Websites als Passwort verwendet 
	zu werden. Zur Erzeugung von Zufallszahlen haben wir die 
	Verteilungsfunktion(distribution) von C++ verwendet.*/
	void generateRandomPassword(wxMouseEvent& event);
};

