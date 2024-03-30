#include "SearchBar.h"

SearchBar::SearchBar(wxWindow* parent, wxSize size)
	: wxWindow(parent, wxID_ANY, wxDefaultPosition, size)
{
	wxFont textFont(wxFontInfo(13).FaceName("Dosis Light").Bold());

	wxString barString = (R"(<svg viewBox="0 0 24 24" fill="#000000" class="w-6 h-6"><path fill-rule="evenodd" d="M3 6.75A.75.75 0 0 1 3.75 6h16.5a.75.75 0 0 1 0 1.5H3.75A.75.75 0 0 1 3 6.75ZM3 12a.75.75 0 0 1 .75-.75h16.5a.75.75 0 0 1 0 1.5H3.75A.75.75 0 0 1 3 12Zm0 5.25a.75.75 0 0 1 .75-.75h16.5a.75.75 0 0 1 0 1.5H3.75a.75.75 0 0 1-.75-.75Z" clip-rule="evenodd" /></svg>)");
	barSVG = new SVGPanel(
		this, wxSize(30, 30),
		barString,
		wxColor(255, 181, 52),
		wxColor(255, 225, 93)
	);

	searchBar = new TextBox(this, wxEmptyString, wxSize(size.GetWidth() - 60, size.GetHeight()), wxTE_PROCESS_ENTER, wxColor(255, 181, 52), wxColor(255, 225, 93), wxColor(228, 233, 237), wxColor(32, 33, 33), textFont);
	wxFont searchFont(wxFontInfo(13).FaceName("Dosis").Bold());
	searchBar->SetFont(searchFont);

	wxString searchString = (R"(<svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="#000000" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="m21 21-5.197-5.197m0 0A7.5 7.5 0 1 0 5.196 5.196a7.5 7.5 0 0 0 10.607 10.607Z" /></svg>)");
	searchSVG = new SVGPanel(
		this, wxSize(30, 30),
		searchString,
		wxColor(255, 181, 52),
		wxColor(255, 225, 93)
	);

	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(barSVG, 0, wxEXPAND, 0);
	mainSizer->Add(searchBar, 1, wxEXPAND, 0);
	mainSizer->Add(searchSVG, 0, wxEXPAND, 0);
	SetSizer(mainSizer);
}
wxTextCtrl* SearchBar::get_searchBar()
{
	return searchBar->get_textCtrl();
}
SVGPanel* SearchBar::get_barSVG()
{
	return barSVG;
}
SVGPanel* SearchBar::get_searchSVG()
{
	return searchSVG;
}
void SearchBar::reset()
{
	searchBar->get_textCtrl()->SetValue(wxEmptyString);
}
