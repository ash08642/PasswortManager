#include "TextBox.h"

TextBox::TextBox(wxWindow* parent, wxString text, wxSize size, long style, wxColor borderColor, wxColor background, wxColor foreground, wxFont font)
	: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	this->SetBackgroundColour(borderColor);
	textCtrl = new wxTextCtrl(this, wxID_ANY, text, wxDefaultPosition, wxSize(size.GetWidth() - 4, size.GetHeight() - 4), wxNO_BORDER | wxTE_RICH | wxTE_RICH2 | wxTE_NOHIDESEL | style);
	textCtrl->SetFont(font);
	textCtrl->SetBackgroundColour(background);
	textCtrl->SetForegroundColour(foreground);

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(textCtrl, 0, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 2);
	SetSizerAndFit(sizer);

	textCtrl->Bind(wxEVT_SET_FOCUS, &TextBox::OnEnterPanel, this);
	textCtrl->Bind(wxEVT_KILL_FOCUS, &TextBox::OnLeavePanel, this);
}

wxTextCtrl* TextBox::get_textCtrl()
{
	return textCtrl;
}

void TextBox::OnEnterPanel(wxEvent& event)
{
	//wxMessageBox("Focused");
	this->SetBackgroundColour(wxColor(
		this->GetBackgroundColour().GetRed() * 1.80,
		this->GetBackgroundColour().GetBlue() * 1.80,
		this->GetBackgroundColour().GetGreen() * 1.80
	));
	Refresh();
	event.Skip();
}
void TextBox::OnLeavePanel(wxEvent& event)
{
	//wxMessageBox("Lost Focus");
	this->SetBackgroundColour(wxColor(
		this->GetBackgroundColour().GetRed() / 1.80,
		this->GetBackgroundColour().GetBlue() / 1.80,
		this->GetBackgroundColour().GetGreen() / 1.80
	));
	Refresh();
	event.Skip();
}
