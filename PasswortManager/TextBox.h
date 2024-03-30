#pragma once
#include <wx/wx.h>

class TextBox : public wxWindow
{
public:
	TextBox(wxWindow* parent, wxString text, wxSize size, long style, wxColor primary_borderColor, wxColor secondary_borderColor, wxColor background, wxColor foreground, wxFont font);
	wxTextCtrl* get_textCtrl();
private:
	wxTextCtrl* textCtrl;

	wxColor primaryBorderColor;
	wxColor secondaryBorderColor;

	void OnEnterPanel(wxEvent& event);
	void OnLeavePanel(wxEvent& event);
};