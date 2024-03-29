#include "MasterAccount.h"

wxString MasterAccount::get_username()
{
	return username;
}
wxString MasterAccount::get_password()
{
	return password;
}
std::string MasterAccount::get_key()
{
	return key;
}
std::string MasterAccount::get_auth_key()
{
	return auth_key;
}

void MasterAccount::Sign_InUp(wxString id, wxString pass)
{
	username = id;
	password = pass;
	key = Crypto::Hash2_SHA256(password.ToStdString(), 20000, username.ToStdString());
	auth_key = Crypto::Hash2_SHA256(password.ToStdString(), 10000, username.ToStdString());
}
void MasterAccount::SignOut()
{
	username = "";
	password = "";
	key = "";
	auth_key = "";
}