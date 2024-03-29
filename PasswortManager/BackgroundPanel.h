#pragma once
#include <wx/wx.h>

class BackgroundPanel : public wxPanel
{
    wxImage image;
    wxBitmap resized;
    int w, h;

public:
    BackgroundPanel(wxWindow* parent, wxSize size, wxString file, wxBitmapType format);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};




