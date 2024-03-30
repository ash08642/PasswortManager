#include "SVGPanel.h"

SVGPanel::SVGPanel(wxWindow* parent, wxSize size, wxString svg, wxColor primary_color, wxColor secondary_color, bool hoverable)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, size)
{
    primaryColor = primary_color;
    secondaryColor = secondary_color;

    SetBackgroundColour(primaryColor);
    wxBitmapBundle bundle = wxBitmapBundle::FromSVG(svg.mb_str(), size);
    if (!bundle.IsOk()) wxMessageBox("BUNDLE NOT OK");
    pic = new wxStaticBitmap(this, wxID_ANY, bundle);
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(pic, 0, wxALIGN_CENTRE, 0);
    SetSizer(sizer);

    if (hoverable)
    {
        pic->Bind(wxEVT_ENTER_WINDOW, &SVGPanel::OnEnterPanel, this);
        pic->Bind(wxEVT_LEAVE_WINDOW, &SVGPanel::OnLeavePanel, this);
    }
}
void SVGPanel::OnEnterPanel(wxMouseEvent& event) {
    this->SetBackgroundColour(secondaryColor);
    Refresh();
}

void SVGPanel::OnLeavePanel(wxMouseEvent& event) {
    this->SetBackgroundColour(primaryColor);
    Refresh();
}

wxStaticBitmap* SVGPanel::get_clickablePanel()
{
    return pic;
}