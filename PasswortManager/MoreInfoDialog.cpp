#include "MoreInfoDialog.h"

MoreInfoDialog::MoreInfoDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "More Information", wxDefaultPosition, wxSize(300, 400))
{
	this->SetBackgroundColour(wxColor(20, 37, 43));
	wxFont labelFont(wxFontInfo(14).FaceName("Dosis").Bold());

	wxStaticText* text = new wxStaticText(this, wxID_ANY,
		R"(This is a basic second generation password manager that
employs sophisticated algorithms to protect passwords with
a master password.
The master password is the key to unlock the vault. So only
the master password needs to be remembered to secure all
other passwords.

Author:
	ahmad.abeer11@gmail.com)"
	);
	text->SetFont(labelFont);
	text->SetForegroundColour(wxColor(180, 235, 255));

	wxHyperlinkCtrl* github = new wxHyperlinkCtrl(this, wxID_ANY, "Github", "https://github.com/ash08642");
	labelFont.SetUnderlined(true);
	github->SetFont(labelFont);
	github->SetForegroundColour(wxColor(180, 235, 255));

	wxButton* Ok = new wxButton(this, wxID_OK, "OK", wxDefaultPosition, wxSize(60, 30));
	Ok->SetBackgroundColour(wxColor(141, 247, 221));
	Ok->SetFocus();

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(text, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 15);
	sizer->Add(github, 0, wxLEFT | wxRIGHT | wxBOTTOM, 15);
	sizer->Add(Ok, 0, wxLEFT | wxRIGHT | wxBOTTOM, 20);
	SetSizerAndFit(sizer);
}