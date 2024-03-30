#include "wxImagePanel.h"

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
 // catch paint events
    EVT_PAINT(wxImagePanel::paintEvent)
    EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()

    wxImagePanel::wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, wxSize size) :
    wxWindow(parent, wxID_ANY, wxDefaultPosition, size)
{
    image.LoadFile(file, format);
    w = -1;
    h = -1;
    this->SetBackgroundColour(wxColor(189, 195, 199));
}

void wxImagePanel::paintEvent(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering
 */
void wxImagePanel::render(wxDC& dc)
{
    int neww, newh;
    dc.GetSize(&neww, &newh);

    if (neww != w || newh != h)
    {
        wxBitmapHelpers::Rescale(image, wxSize(neww, newh));
        resized = image;
        w = neww;
        h = newh;
        dc.DrawBitmap(resized, 0, 0, false);
    }
    else {
        dc.DrawBitmap(resized, 0, 0, false);
    }
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}