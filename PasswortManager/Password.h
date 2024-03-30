#pragma once

#include <wx/wx.h>
#include <wx/textfile.h>

#include "Crypto.h"

class Password
{
private:
	std::string plain_text;
	std::string cipher_text;
	std::string salt;
	unsigned char Key[32];
	unsigned char IV[16];
	std::string masterKey;

public:
	Password(wxString plaintext, wxString master_key);
	Password(wxString master_key, wxString ciphertext, wxString _salt);
	~Password();

	std::string get_plain_text();
	std::string get_cipher_text();
	std::string get_salt();
	wxString getWxString();
};


