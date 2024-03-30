#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class CustomButton : public wxWindow
{
private:
    wxStaticText* label;
    bool hoverable;
    bool isLabelHoverable;

    wxColor primaryColor;
    wxColor secondaryColor;
public:
    CustomButton(wxWindow* parent, wxSize size, wxColor primary_color, wxColor secondary_color, wxString text, bool hoverable, wxFont font, wxColor fontColor, bool labelHoverable);
    CustomButton(wxWindow* parent, wxSize size, wxColor primary_color, wxColor secondary_color, wxString text, wxString text2);

    wxStaticText* getClickablePanel();

    void OnLeavePanel(wxMouseEvent& event);
    void OnEnterPanel(wxMouseEvent& event);
};

