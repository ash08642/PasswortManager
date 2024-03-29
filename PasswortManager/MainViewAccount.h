#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "AccountPanel.h"
#include "CustomButton.h"
#include "AppSetting.h"

class MainViewAccount : public wxWindow
{
public:
	MainViewAccount(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, AccountPanel* account_panel, AppSetting* app_Setting);

	wxStaticText* get_EditButton();
	wxStaticText* get_DeleteButton();

	AccountPanel* get_accountPanel();
private:
	AccountPanel* accountPanel;
	CustomButton* Edit;
	CustomButton* Delete;

	AppSetting* appSetting;
};


