#pragma once

#include <wx/wx.h>
#include "SVGPanel.h"
#include "TextBox.h"

class SearchBar : public wxWindow
{
public:
	SearchBar(wxWindow* parent, wxSize size);
	wxTextCtrl* get_searchBar();
	SVGPanel* get_barSVG();
	SVGPanel* get_searchSVG();
	void reset();
private:
	SVGPanel* barSVG;
	TextBox* searchBar = nullptr;
	TextBox* readOnlySearchBar = nullptr;
	SVGPanel* searchSVG;
	wxSizer* mainSizer;
};
