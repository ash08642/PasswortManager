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
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC& dc)
{
    int neww, newh;
    dc.GetSize(&neww, &newh);

    if (neww != w || newh != h)
    {
        wxBitmapHelpers::Rescale(image, wxSize(neww, newh));
        resized = image;
        //resized = wxBitmap(image.Rescale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
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