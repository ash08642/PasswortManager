#include "BackgroundPanel.h"
BEGIN_EVENT_TABLE(BackgroundPanel, wxPanel)
 // catch paint events
    EVT_PAINT(BackgroundPanel::paintEvent)

END_EVENT_TABLE()

BackgroundPanel::BackgroundPanel(wxWindow* parent, wxSize size, wxString file, wxBitmapType format)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
{
    // load the file... ideally add a check to see if loading was successful
    image.LoadFile(file, format);
}

void BackgroundPanel::paintEvent(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void BackgroundPanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

//Actual Rendering happens here
void BackgroundPanel::render(wxDC& dc)
{
    dc.DrawBitmap(image, 0, 0, false);
}