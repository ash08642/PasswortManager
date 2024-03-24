#pragma once
#include <wx/wx.h>
#include <vector>
#include "Team.h"

class MasterAccount
{
private:
	short id;
	wxString identity;
	wxString master_Password;
	wxString privateKey;
	wxString publicKey;
	wxDateTime dateCreated;
	wxDateTime dateUpdated;
	std::vector<Team> teams;
	std::vector<wxString> accounts;

public:
	void set_masterAccount(std::string iden, std::string pass);
};

