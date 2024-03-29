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
	std::string master_pass;
public:

	Password();
	Password(wxString plaintext, wxString masterpass);
	Password(wxString masterpass, wxString ciphertext, wxString _salt);
	~Password();

	std::string get_plain_text();
	std::string get_cipher_text();
	std::string get_salt();
	wxString getWxString();
};


