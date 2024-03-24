#pragma once

#include <wx/wx.h>
#include <wx/bmpbndl.h>

class SVGPanel : public wxWindow
{
public:
	SVGPanel(wxWindow* parent, wxSize size, wxString svg, wxColor color, bool hoverable = true);
	wxStaticBitmap* get_clickablePanel();
private:
	wxStaticBitmap* pic;
	void OnEnterPanel(wxMouseEvent& event);
	void OnLeavePanel(wxMouseEvent& event);
};
