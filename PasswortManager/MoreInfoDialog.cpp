#include "MoreInfoDialog.h"

MoreInfoDialog::MoreInfoDialog(wxWindow* parent, AppSetting* app_setting) : wxDialog(parent, wxID_ANY, "More Information", wxDefaultPosition, wxSize(300, 400))
{
	this->SetBackgroundColour(*app_setting->order21);
	wxFont labelFont(wxFontInfo(14).FaceName("Dosis-Light"));

	wxStaticText* text = new wxStaticText(this, wxID_ANY, app_setting->selected_language2[AppSetting::TextKeys::InfoParagraph]
	);
	text->SetFont(labelFont);
	text->SetForegroundColour(wxColor(0, 0, 0));

	wxHyperlinkCtrl* github = new wxHyperlinkCtrl(this, wxID_ANY, "Github", "https://github.com/ash08642/PasswortManager/tree/master");
	labelFont.SetUnderlined(true);
	github->SetFont(labelFont);
	github->SetForegroundColour(*app_setting->order6);

	wxButton* Ok = new wxButton(this, wxID_OK, "OK", wxDefaultPosition, wxSize(60, 30));
	Ok->SetBackgroundColour(*app_setting->order61);
	Ok->SetFocus();

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(text, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 15);
	sizer->Add(github, 0, wxLEFT | wxRIGHT | wxBOTTOM, 15);
	sizer->Add(Ok, 0, wxLEFT | wxRIGHT | wxBOTTOM, 20);
	SetSizerAndFit(sizer);
}