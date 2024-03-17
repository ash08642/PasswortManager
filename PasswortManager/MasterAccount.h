#pragma once
#include <wx/wx.h>
#include <vector>

#include "Team.h"

class MasterAccount
{
	short id;
	wxString identity;
	wxString master_Password;
	wxString privateKey;
	wxString publicKey;
	wxDateTime dateCreated;
	wxDateTime dateUpdated;
	std::vector<Team> teams;
	std::vector<wxString> accounts;
};

