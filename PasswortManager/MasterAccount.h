#pragma once

#include <wx/wx.h>
#include <wx/textfile.h>
#include <sstream>
#include <vector>
#include "Crypto.h"

class MasterAccount
{
private:
	wxString username;
	wxString password;
	std::string key;
	std::string auth_key;

public:
	wxString get_username();
	wxString get_password();
	std::string get_key();
	std::string get_auth_key();

	void Sign_InUp(wxString id, wxString pass);
	void SignOut();
};

