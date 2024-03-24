#pragma once
#include <wx/wx.h>

class TextBox : public wxWindow
{
public:
	TextBox(wxWindow* parent, wxString text, wxSize size, long style, wxColor borderColor, wxColor background, wxColor foreground, wxFont font);
	wxTextCtrl* get_textCtrl();
private:
	wxTextCtrl* textCtrl;

	void OnEnterPanel(wxEvent& event);
	void OnLeavePanel(wxEvent& event);
};