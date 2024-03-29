#include "Password.h"

Password::Password()
{}
Password::Password(wxString plaintext, wxString masterpass)
{
	plain_text = plaintext.ToStdString();
	master_pass = masterpass.ToStdString();

	salt = Crypto::generateSalt();

	const EVP_CIPHER* cipherInfo = EVP_aes_256_cbc();
	int iklen = EVP_CIPHER_key_length(cipherInfo);
	int ivlen = EVP_CIPHER_iv_length(cipherInfo);
	Crypto::PBKDF2_derive_key_iv(master_pass, salt, Key, iklen, IV, ivlen);
	//Crypto::PBKDF2_derive_key_iv("hello", "salt", Key, 32, IV, 16);
	unsigned char cipher[128];
	cipher_text = Crypto::encrypt((unsigned char*)plain_text.c_str(), plain_text.length(), Key, IV, cipher);


	wxTextFile file(wxT("data/test.txt"));

}
Password::Password(wxString masterpass, wxString ciphertext, wxString _salt)
{
	cipher_text = ciphertext.ToStdString();
	master_pass = masterpass.ToStdString();
	salt = _salt.ToStdString();
	
	const EVP_CIPHER* cipherInfo = EVP_aes_256_cbc();
	int iklen = EVP_CIPHER_key_length(cipherInfo);
	int ivlen = EVP_CIPHER_iv_length(cipherInfo);
	Crypto::PBKDF2_derive_key_iv(master_pass, salt, Key, iklen, IV, ivlen);

	salt = _salt.ToStdString();

	unsigned char plain[128];
	plain_text = Crypto::decrypt(Crypto::hexStringToChar(cipher_text), cipher_text.length() / 2, Key, IV, plain);
}
Password::~Password()
{
	/*delete plain_text;
	delete cipher_text;
	delete salt_Key;
	delete salt_IV;
	delete Key;
	delete IV;*/
}

std::string Password::get_plain_text()
{
	return plain_text;
}

std::string Password::get_cipher_text()
{
	return cipher_text;
}

std::string Password::get_salt()
{
	return salt;
}

wxString Password::getWxString()
{
	wxString result = salt + ";pause;" + cipher_text;
	return result;
}
