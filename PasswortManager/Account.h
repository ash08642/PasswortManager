#pragma once

#include <wx/wx.h>
#include <map>
#include <wx/datetime.h>
#include <wx/textfile.h>

#include <openssl/evp.h>
#include <openssl/kdf.h>
#include <openssl/params.h>

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Password.h"
#include "Crypto.h"
#include "HttpClient.h"

class Account
{
private:
	int accountId;
	wxString masterAccountIdentity;
	wxString platform;
	wxString identifier;	//username or email
	wxDateTime createdAt;
	wxDateTime updatedAt;
	Password* passwort;

public:
	Account();
	Account(wxString masterAccId, wxString platf, wxString iden, wxString plainText, wxString master_key);
	Account(
		int account_id,
		wxString master_account_identity,
		wxString _platform,
		wxString _identifier,	//username or email
		wxString created_at,
		wxString updated_at,
		wxString cipher_text,
		wxString salt,
		wxString master_key
	);
	~Account();

	wxString get_platform();
	wxString get_identifier();
	wxString get_password();
	wxString get_createdAt();
	wxString get_updated_At();

	void update_account(wxString neu_platform, wxString neu_identifier, wxString new_plain_text, wxString master_pass);
	void update_account(wxString neu_platform, wxString neu_identifier);

	void set_password(wxString new_plain_text, wxString master_pass);
	void set_platform(wxString neu_platform);
	void set_identifier(wxString neu_identifier);

	bool isTimeSame();
	wxString getString();
	bool DeleteFromDB(HttpClient* httpCleint);
	void AddToDB(HttpClient* httpCleint);
	void UpdateInDB(HttpClient* httpCleint);
};

