#include "Account.h"

std::vector<wxString> DevideString3(std::string line, std::string delimiter)
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

Account::Account()
{
}

Account::Account(wxString masterAccId, wxString platf, wxString iden, wxString plainText, wxString master_key)
	:
	platform{ platf },
	identifier{ iden },
	masterAccountIdentity{ masterAccId }
{
	createdAt = wxDateTime(wxDateTime::Now());
	updatedAt = wxDateTime(createdAt);
	createdAt.SetCountry(wxDateTime::Country::Germany);
	updatedAt.SetCountry(wxDateTime::Country::Germany);
	passwort = new Password(plainText, master_key);
}

Account::Account(int account_id, wxString master_account_identity, wxString _platform, wxString _identifier, wxString created_at, wxString updated_at, wxString cipher_text, wxString salt, wxString master_key) :
	accountId{account_id},
	masterAccountIdentity{master_account_identity},
	platform{_platform},
	identifier{_identifier}	//username or 
{
	//createdAt.ParseFormat(created_at);
	//updatedAt.ParseFormat(updated_at);
	createdAt.ParseDate(created_at);
	createdAt.ParseTime(created_at);
	updatedAt.ParseDate(updated_at);
	updatedAt.ParseTime(updated_at);
	createdAt.SetCountry(wxDateTime::Country::Germany);
	updatedAt.SetCountry(wxDateTime::Country::Germany);
	passwort = new Password(master_key, cipher_text, salt);
}

Account::~Account()
{
	delete passwort;
}

wxString Account::get_platform()
{
	return platform;
}

wxString Account::get_identifier()
{
	return identifier;
}

wxString Account::get_password()
{
	return passwort->get_plain_text();
}

wxString Account::get_createdAt()
{
	return createdAt.Format("%d %a %B %Y");
}
wxString Account::get_updated_At()
{
	return updatedAt.Format("%d %a %B %Y");
}

void Account::update_account(wxString neu_platform, wxString neu_identifier, wxString new_plain_text, wxString master_pass)
{
	set_password(new_plain_text, master_pass);
	set_platform(neu_platform);
	set_identifier(neu_identifier);
	updatedAt = wxDateTime::Now();
}

void Account::update_account(wxString neu_platform, wxString neu_identifier)
{
	set_platform(neu_platform);
	set_identifier(neu_identifier);
	updatedAt = wxDateTime::Now();
}
void Account::set_password(wxString new_plain_text, wxString master_pass)
{
	delete passwort;
	passwort = new Password(new_plain_text, master_pass);
}

void Account::set_platform(wxString neu_platform)
{
	platform = neu_platform;
}

void Account::set_identifier(wxString neu_identifier)
{
	identifier = neu_identifier;
}

bool Account::isTimeSame()
{
	if (createdAt.IsEqualTo(updatedAt))
	{
		std::cout << "time are equal" << std::endl;
		return true;
	}
	std::cout << "time are not equal" << std::endl;
	return false;
}

wxString Account::getString()
{
	wxString master_account_id;
	//master_account_id << masterAccountId;
	wxString account_id;
	account_id << accountId;
	wxString result = master_account_id + ";pause;"
		+ account_id + ";pause;"
		+ platform + ";pause;"
		+ identifier + +";pause;"
		+ createdAt.FormatDate() + ";pause;"
		+ createdAt.FormatTime() + ";pause;"
		+ updatedAt.FormatDate() + +";pause;"
		+ updatedAt.FormatTime() + +";pause;"
		+ passwort->getWxString();

	return result;
}

bool Account::DeleteFromDB(HttpClient* httpCleint)
{
	std::vector<std::string> keys{ "saved_account_id", "master_account_identity" };
	std::vector<std::string> values{ std::to_string(accountId), masterAccountIdentity.ToStdString() };
	std::string res = httpCleint->post_req("/deleteAccount", keys, values);
	if (!res.compare("error"))
	{
		return false;
	}
	return true;
}

void Account::AddToDB(HttpClient* httpCleint)
{
	std::vector<std::string> keys{"master_account_identity", "platform", "saved_account_identity", "pass", "created_at", "updated_at", "salt"};
	std::vector<std::string> values{ masterAccountIdentity.ToStdString(), platform.ToStdString(), identifier.ToStdString(), passwort->get_cipher_text(), createdAt.FormatISODate().ToStdString(), updatedAt.FormatISODate().ToStdString(), passwort->get_salt()};
	accountId = stoi(httpCleint->post_req("/addAccount", keys, values));
}

void Account::UpdateInDB(HttpClient* httpCleint)
{
	std::vector<std::string> keys{ "saved_account_id", "master_account_identity", "platform", "saved_account_identity", "pass", "created_at", "updated_at", "salt" };
	std::vector<std::string> values{ std::to_string(accountId), masterAccountIdentity.ToStdString(), platform.ToStdString(), identifier.ToStdString(), passwort->get_cipher_text(), createdAt.FormatISODate().ToStdString(), updatedAt.FormatISODate().ToStdString(), passwort->get_salt()};
	httpCleint->post_req("/updateAccount", keys, values);
}

//std::vector<Account*> Account::getAccountsFromFile(wxString masterPassword)
//{
//	std::vector<Account*> result(0);
//	wxString line;
//	wxTextFile tfile;
//	tfile.Open(wxT("data/AccountsFile.txt"));
//	line = tfile.GetFirstLine();
//	while (!tfile.Eof())
//	{
//		if (line.length() > 10)
//		{
//			result.push_back(new Account(line, masterPassword.ToStdString()));
//			//result.resize(Accounts.size() + 1);
//		}
//		line = tfile.GetNextLine();
//	}
//	tfile.Close();
//	return result;
//}