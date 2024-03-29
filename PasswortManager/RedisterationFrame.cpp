#include "RedisterationFrame.h"
BEGIN_EVENT_TABLE(RedisterationFrame, wxFrame)
EVT_PAINT(RedisterationFrame::paintEvent)

END_EVENT_TABLE()

RedisterationFrame::RedisterationFrame(const wxString& title, const wxPoint& pos, const wxSize& size, AppSetting* settings, MasterAccount* mas_acc, HttpClient* client)
	:wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	wxIcon app_icon;

	appSetting = settings;
	masterAccount = mas_acc;
	httpCleint = client;

	wxImage::AddHandler(new wxPNGHandler);
	app_icon.LoadFile("Images/beautiful_flat-style_logo_desi.png", wxBITMAP_TYPE_PNG);

	if (app_icon.IsOk()) {
		SetIcon(app_icon);
	}
	else
	{
		wxMessageBox("App icon failed");
	}

	if (!wxFont::AddPrivateFont("Fonts/static/Dosis-Bold.ttf"))
	{
		wxMessageBox("Dosis-Bold Failed to load");
	}
	if (!wxFont::AddPrivateFont("Fonts/static/Dosis-Light.ttf"))
	{
		wxMessageBox("Dosis-Light Failed to load");
	}
	//this->SetBackgroundColour(wxColor(40, 40, 40));
	/*if (!wxFont::AddPrivateFont("Fonts/Dosis-Bold.ttf"))
	{
		wxMessageBox("Dosis-Bold Failed to load");
	}
	if (!wxFont::AddPrivateFont("Fonts/Dosis-Light.ttf"))
	{
		wxMessageBox("Dosis-Light Failed to load");
	}*/
	sizer = new wxBoxSizer(wxVERTICAL);
	signUpPanel = new SignUpPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), appSetting);
	signInPanel = new SignInPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), appSetting);
	sizer->AddStretchSpacer(1);
	sizer->Add(signInPanel, 0, wxALIGN_CENTER);
	sizer->Add(signUpPanel, 0, wxALIGN_CENTER);
	sizer->AddStretchSpacer(1);

	signUpPanel->Hide();

	signInButton = signInPanel->get_signInButton();
	signUpButton = signUpPanel->get_signUpButton();

	signUpPanel->get_alreadyRegisteredButton()->Bind(wxEVT_LEFT_DOWN, &RedisterationFrame::showSignIn, this);
	signInPanel->get_goCreateAccountButton()->Bind(wxEVT_LEFT_DOWN, &RedisterationFrame::showSignUp, this);
	SetSizer(sizer);
	image.LoadFile("Images/darkbg.png", wxBITMAP_TYPE_PNG);
}

void RedisterationFrame::showSignIn(wxMouseEvent& event)
{
	signUpPanel->Show(false);
	signInPanel->Show(true);
	Layout();
}

void RedisterationFrame::showSignUp(wxMouseEvent& event)
{
	signInPanel->Show(false);
	signUpPanel->Show(true);
	Layout();
}

wxStaticText* RedisterationFrame::get_signInButton()
{
	return signInButton;
}
wxStaticText* RedisterationFrame::get_signUpButton()
{
	return signUpButton;
}

bool RedisterationFrame::validate_signUpData()
{
	if (signUpPanel->get_identtity() == wxEmptyString || signUpPanel->get_pass() == wxEmptyString || signUpPanel->get_confirmPass() == wxEmptyString)
	{
		wxMessageBox(appSetting->selected_language[AppSetting::TextKeys::PleaseFillAllFields]);
		return false;
	}
	if (signUpPanel->get_pass() == signUpPanel->get_confirmPass())
	{
		masterAccount->Sign_InUp(signUpPanel->get_identtity(), signUpPanel->get_pass());

		std::vector<std::string> keys = { "identity", "password" };
		std::vector<std::string> values = { 
			masterAccount->get_username().ToStdString(),
			masterAccount->get_auth_key()
		};
		wxString response = httpCleint->post_req("/signUp", keys, values);
		if (response != "error")
		{
			return true;
		}
		return false;
	}

	wxMessageBox(appSetting->selected_language[AppSetting::TextKeys::PasswordsDoNotMatch]);
	return false;
}
bool RedisterationFrame::validate_signInData()
{
	if (signInPanel->get_identtity() == wxEmptyString || signInPanel->get_pass() == wxEmptyString)
	{
		wxMessageBox(appSetting->selected_language[AppSetting::TextKeys::PleaseFillAllFields]);
		return false;
	}

	masterAccount->Sign_InUp(signInPanel->get_identtity(), signInPanel->get_pass());

	std::vector<std::string> keys = { "identity", "password" };
	std::vector<std::string> values = {
		masterAccount->get_username().ToStdString(),
		masterAccount->get_auth_key()
	};
	
	wxString response = httpCleint->get_req("/login", keys, values);
	if (response != "error")
	{
		return true;
	}
	return false;
}

void RedisterationFrame::clear_fields()
{
	signInPanel->clear_fields();
	signUpPanel->clear_fields();
}

void RedisterationFrame::paintEvent(wxPaintEvent& evt)
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
void RedisterationFrame::paintNow()
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
void RedisterationFrame::render(wxDC& dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}