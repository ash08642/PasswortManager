#pragma once

#include <wx/wx.h>
#include <wx/bmpbndl.h>

class SVGPanel : public wxWindow
{
public:
	SVGPanel(wxWindow* parent, wxSize size, wxString svg, wxColor primary_color, wxColor secondary_color, bool hoverable = true);
	wxStaticBitmap* get_clickablePanel();
private:
	wxStaticBitmap* pic;

	wxColor primaryColor;
	wxColor secondaryColor;

	void OnEnterPanel(wxMouseEvent& event);
	void OnLeavePanel(wxMouseEvent& event);
};
