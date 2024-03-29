#include "AccountPanel.h"

std::vector<wxString> DevideString5(std::string line, std::string delimiter)
{
	std::vector<wxString> result(0);
	size_t pos = 0;
	std::string token;
	wxString temp;
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		result.resize(result.size() + 1);
		temp = token;
		result[result.size() - 1] = temp;
		line.erase(0, pos + delimiter.length());
	}
	result.resize(result.size() + 1);
	temp = line;
	result[result.size() - 1] = temp;

	return result;
}

AccountPanel::AccountPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int i, std::vector<AccountPanel*>& cont, Account* konto) : wxWindow(parent, id, pos, size), index{ i }, container{ cont }, account{ konto }
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->SetBackgroundColour(wxColor(73, 120, 120));
	isSelected = false;

	wxString platformString(R"(<svg viewBox="0 0 20 20" fill="#000000" class="w-5 h-5"><path d="M16.555 5.412a8.028 8.028 0 0 0-3.503-2.81 14.899 14.899 0 0 1 1.663 4.472 8.547 8.547 0 0 0 1.84-1.662ZM13.326 7.825a13.43 13.43 0 0 0-2.413-5.773 8.087 8.087 0 0 0-1.826 0 13.43 13.43 0 0 0-2.413 5.773A8.473 8.473 0 0 0 10 8.5c1.18 0 2.304-.24 3.326-.675ZM6.514 9.376A9.98 9.98 0 0 0 10 10c1.226 0 2.4-.22 3.486-.624a13.54 13.54 0 0 1-.351 3.759A13.54 13.54 0 0 1 10 13.5c-1.079 0-2.128-.127-3.134-.366a13.538 13.538 0 0 1-.352-3.758ZM5.285 7.074a14.9 14.9 0 0 1 1.663-4.471 8.028 8.028 0 0 0-3.503 2.81c.529.638 1.149 1.199 1.84 1.66ZM17.334 6.798a7.973 7.973 0 0 1 .614 4.115 13.47 13.47 0 0 1-3.178 1.72 15.093 15.093 0 0 0 .174-3.939 10.043 10.043 0 0 0 2.39-1.896ZM2.666 6.798a10.042 10.042 0 0 0 2.39 1.896 15.196 15.196 0 0 0 .174 3.94 13.472 13.472 0 0 1-3.178-1.72 7.973 7.973 0 0 1 .615-4.115ZM10 15c.898 0 1.778-.079 2.633-.23a13.473 13.473 0 0 1-1.72 3.178 8.099 8.099 0 0 1-1.826 0 13.47 13.47 0 0 1-1.72-3.178c.855.151 1.735.23 2.633.23ZM14.357 14.357a14.912 14.912 0 0 1-1.305 3.04 8.027 8.027 0 0 0 4.345-4.345c-.953.542-1.971.981-3.04 1.305ZM6.948 17.397a8.027 8.027 0 0 1-4.345-4.345c.953.542 1.971.981 3.04 1.305a14.912 14.912 0 0 0 1.305 3.04Z" /></svg>)");
	platformSVG = new SVGPanel(this, wxSize(15, 15), platformString, this->GetBackgroundColour(), false);

	wxString identifierString(R"(<svg viewBox="0 0 20 20" fill="#000000" class="w-5 h-5"><path d="M10 8a3 3 0 1 0 0-6 3 3 0 0 0 0 6ZM3.465 14.493a1.23 1.23 0 0 0 .41 1.412A9.957 9.957 0 0 0 10 18c2.31 0 4.438-.784 6.131-2.1.43-.333.604-.903.408-1.41a7.002 7.002 0 0 0-13.074.003Z" /></svg>)");
	identifierSVG = new SVGPanel(this, wxSize(15, 15), identifierString, this->GetBackgroundColour(), false);
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(platformSVG, 1);
	sizer->Add(identifierSVG, 1);
	SetSizer(sizer);

	this->Bind(wxEVT_PAINT, &AccountPanel::OnPaint, this);
	this->Bind(wxEVT_ENTER_WINDOW, &AccountPanel::OnEnterPanel, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &AccountPanel::OnLeavePanel, this);
	identifierSVG->get_clickablePanel()->Bind(wxEVT_ENTER_WINDOW, &AccountPanel::OnEnterPanel, this);
	identifierSVG->get_clickablePanel()->Bind(wxEVT_LEAVE_WINDOW, &AccountPanel::OnLeavePanel, this);
	platformSVG->get_clickablePanel()->Bind(wxEVT_ENTER_WINDOW, &AccountPanel::OnEnterPanel, this);
	platformSVG->get_clickablePanel()->Bind(wxEVT_LEAVE_WINDOW, &AccountPanel::OnLeavePanel, this);
}
AccountPanel::~AccountPanel()
{
	delete account;
}

void AccountPanel::OnPaint(wxPaintEvent& evt)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

	if (gc)
	{
		wxPoint rectOrigin = this->FromDIP(wxPoint(0, 0));
		wxSize rectSize = this->FromDIP(this->GetSize());

		//gc->SetBrush(*wxRED_BRUSH);
		//gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

		wxFont platformTextFont(wxFontInfo(13).FaceName("Dosis"));
		gc->SetFont(platformTextFont, *wxWHITE);
		wxString platformText = account->get_platform();
		double platformTextWidth, platformTextHeigth;
		gc->GetTextExtent(platformText, &platformTextWidth, &platformTextHeigth);
		gc->DrawText(
			platformText,
			20.0,
			rectSize.GetHeight() * 0.25 - (platformTextHeigth / 2.0)
		);

		wxFont identifierTextFont(wxFontInfo(12).FaceName("Dosis"));
		gc->SetFont(identifierTextFont, *wxWHITE);
		wxString identifierText = account->get_identifier();
		double identifierTextWidth, identifierTextHeigth;
		gc->GetTextExtent(identifierText, &identifierTextWidth, &identifierTextHeigth);
		gc->DrawText(
			identifierText,
			20.0,
			rectSize.GetHeight() * 0.75 - (identifierTextHeigth / 2.0)
		);
		delete gc;
	}
}

Account* AccountPanel::get_account()
{
	return account;
}

bool AccountPanel::is_selected()
{
	return isSelected;
}

void AccountPanel::OnMouseDown()
{
	if (!isSelected)
	{
		this->SetOwnBackgroundColour(wxColor(108, 171, 171));
		identifierSVG->SetOwnBackgroundColour(wxColor(108, 171, 171));
		platformSVG->SetOwnBackgroundColour(wxColor(108, 171, 171));
		isSelected = true;
		for (int i = 0; i < container.size(); i++)
		{
			if (i == index)
			{
				continue;
			}
			container[i]->reset();
		}
		Refresh();
	}
	else
	{
		this->SetOwnBackgroundColour(*wxWHITE);
		isSelected = false;
		Refresh();
	}
}

void AccountPanel::OnEnterPanel(wxMouseEvent& event) {
	if (!isSelected)
	{
		this->SetBackgroundColour(wxColor(93, 150, 150));
		platformSVG->SetBackgroundColour(wxColor(93, 150, 150));
		identifierSVG->SetBackgroundColour(wxColor(93, 150, 150));
		Refresh();
	}
}

void AccountPanel::OnLeavePanel(wxMouseEvent& event) {
	if (!isSelected)
	{
		this->SetBackgroundColour(wxColor(73, 120, 120));
		platformSVG->SetBackgroundColour(wxColor(73, 120, 120));
		identifierSVG->SetBackgroundColour(wxColor(73, 120, 120));
		Refresh();
	}
}

void AccountPanel::reset()
{
	isSelected = false;
	this->SetBackgroundColour(wxColor(73, 120, 120));
	platformSVG->SetBackgroundColour(wxColor(73, 120, 120));
	identifierSVG->SetBackgroundColour(wxColor(73, 120, 120));
	Refresh();
}

void AccountPanel::resetAll(std::vector<AccountPanel*>& vektor)
{
	for (size_t i = 0; i < vektor.size(); i++)
	{
		vektor[i]->reset();
	}
}

void AccountPanel::changeContainerBeforeDeleting()
{
	for (int i = index + 1; i < container.size(); i++)
	{
		container[i]->decrementIndex();
	}
	container.erase(container.begin() + index);
	delete this;
}

void AccountPanel::decrementIndex()
{
	index = index - 1;
}

void AccountPanel::update_account(wxString neu_platform, wxString neu_identifier, wxString new_plain_text, wxString master_pass, wxString oldPass)
{
	if (new_plain_text == oldPass)
	{
		account->update_account(neu_platform, neu_identifier);
		//wxMessageBox("Password Unchanged");
	}
	else
	{
		account->update_account(neu_platform, neu_identifier, new_plain_text, master_pass);
		//wxMessageBox("Password Changed");
	}
}

std::vector<AccountPanel*> AccountPanel::FillFromDB(wxString master_userName, HttpClient* httpCleint, wxString master_key, wxWindow* parent, std::vector<AccountPanel*>& account_panels)
{
	std::vector<std::string> keys{ "master_account_identity" };
	std::vector<std::string> values{ master_userName.ToStdString()};
	std::string res = httpCleint->get_req("/getSavedAccounts", keys, values);
	std::vector<AccountPanel*> result(0);
	std::vector<wxString> spal = DevideString5(res, ";spal;");
	for (size_t i = 0; i < spal.size() - 1; i++)
	{
		std::vector<wxString> col = DevideString5(spal[i].ToStdString(), ";col;");
		Account* account = new Account(std::stoi(col[0].ToStdString()), master_userName, col[2], col[3], col[5], col[6], col[4], col[7], master_key);
		result.push_back(new AccountPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(250, 50), i, account_panels, account));
	}

	return result;
}

wxStaticBitmap* AccountPanel::get_clickable_platformBitmap()
{
	return platformSVG->get_clickablePanel();
}
wxStaticBitmap* AccountPanel::get_clickable_identifierBitmap()
{
	return identifierSVG->get_clickablePanel();
}