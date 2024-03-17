#pragma once
#include <wx/wx.h>
#include <vector>

struct TeamMember
{
	short id_masterAccount;
	short privilage;
};

struct Key
{
	wxString key;
	short privilage;
};

class Team
{
	short id;
	wxString name;
	wxDateTime dateCreated;
	std::vector<TeamMember> teamMembers;
	std::vector<Key> keys;
};

