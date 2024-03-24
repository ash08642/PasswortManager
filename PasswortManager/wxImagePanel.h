#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

class wxImagePanel : public wxWindow
{
    wxBitmap image;
    wxBitmap resized;
    int w, h;

public:
    wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, wxSize size);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};



