#include "CustomButton.h"

CustomButton::CustomButton(wxWindow* parent, wxSize size, wxColor color, wxString text, bool hoverable, wxFont font, wxColor fontColor, bool labelHoverable) :
	wxWindow(parent, wxID_ANY, wxDefaultPosition, size)
{
	this->hoverable = hoverable;
	isLabelHoverable = labelHoverable;
	SetBackgroundColour(color);

	label = new wxStaticText(this, wxID_ANY, text);
	label->SetFont(font);
	label->SetForegroundColour(fontColor);

	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(label, 0, wxALIGN_CENTER | wxALL, 5);
	SetSizerAndFit(sizer);

	label->Bind(wxEVT_ENTER_WINDOW, &CustomButton::OnEnterPanel, this);
	label->Bind(wxEVT_LEAVE_WINDOW, &CustomButton::OnLeavePanel, this);

}

CustomButton::CustomButton(wxWindow* parent, wxSize size, wxColor color, wxString text, wxString text2) :
	wxWindow(parent, wxID_ANY, wxDefaultPosition, size)
{
-	SetBackgroundColour(color);
}

wxStaticText* CustomButton::getClickablePanel()
{
	return label;
}

void CustomButton::OnEnterPanel(wxMouseEvent& event) {
	if (hoverable)
	{
		this->SetBackgroundColour(wxColor(
			this->GetBackgroundColour().GetRed() * 1.80,
			this->GetBackgroundColour().GetBlue() * 1.80,
			this->GetBackgroundColour().GetGreen() * 1.80
		));
	}

	if (isLabelHoverable)
	{
		label->SetForegroundColour(wxColor(
			label->GetForegroundColour().GetRed() * 1.80,
			label->GetForegroundColour().GetBlue() * 1.80,
			label->GetForegroundColour().GetGreen() * 1.80
		));
	}
	Refresh();
}

void CustomButton::OnLeavePanel(wxMouseEvent& event) {
	if (hoverable)
	{
		this->SetBackgroundColour(wxColor(
			this->GetBackgroundColour().GetRed() / 1.80,
			this->GetBackgroundColour().GetBlue() / 1.80,
			this->GetBackgroundColour().GetGreen() / 1.80
		));
	}
	
	if (isLabelHoverable)
	{
		label->SetForegroundColour(wxColor(
			label->GetForegroundColour().GetRed() / 1.80,
			label->GetForegroundColour().GetBlue() / 1.80,
			label->GetForegroundColour().GetGreen() / 1.80
		));
	}
	Refresh();
}
