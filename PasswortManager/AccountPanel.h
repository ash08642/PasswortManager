#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/textfile.h>

#include <vector>
#include "MasterAccount.h"
#include "Account.h"
#include "SVGPanel.h"
#include "HttpClient.h"
#include "AppSetting.h"

class AccountPanel : public wxWindow
{
public:
	AccountPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int i, std::vector<AccountPanel*>& cont, Account* konto, AppSetting* app_setting);
	void reset();
	~AccountPanel();
	Account* get_account();
	bool is_selected();
	void OnMouseDown();
	void changeContainerBeforeDeleting();
	void update_account(wxString neu_platform, wxString neu_identifier, wxString new_plain_text, wxString master_pass, wxString oldPass);
	static void resetAll(std::vector<AccountPanel*>& vektor);
	static std::vector<AccountPanel*> FillFromDB(wxString master_userName, HttpClient* httpCleint, wxString master_key, wxWindow* parent, std::vector<AccountPanel*>& account_panels, AppSetting* app_setting);

	wxStaticBitmap* get_clickable_platformBitmap();
	wxStaticBitmap* get_clickable_identifierBitmap();
private:
	void OnPaint(wxPaintEvent& evt);
	void OnEnterPanel(wxMouseEvent& event);
	void OnLeavePanel(wxMouseEvent& event);

	Account* account;
	bool isSelected = false;
	int index;
	std::vector<AccountPanel*>& container;
	AppSetting* appSetting;

	SVGPanel* platformSVG;
	SVGPanel* identifierSVG;

	void decrementIndex();
};

