#include "Password.h"

Password::Password(wxString plaintext, wxString master_key)
{
	plain_text = plaintext.ToStdString();
	masterKey = master_key.ToStdString();

	salt = Crypto::generateSalt();

	const EVP_CIPHER* cipherInfo = EVP_aes_256_cbc();
	int iklen = EVP_CIPHER_key_length(cipherInfo);
	int ivlen = EVP_CIPHER_iv_length(cipherInfo);
	Crypto::PBKDF2_derive_key_iv(masterKey, salt, Key, iklen, IV, ivlen);
	//Crypto::PBKDF2_derive_key_iv("hello", "salt", Key, 32, IV, 16);
	unsigned char cipher[128];
	cipher_text = Crypto::encrypt((unsigned char*)plain_text.c_str(), plain_text.length(), Key, IV, cipher);
}
Password::Password(wxString master_key, wxString ciphertext, wxString _salt)
{
	cipher_text = ciphertext.ToStdString();
	masterKey = master_key.ToStdString();
	salt = _salt.ToStdString();
	
	const EVP_CIPHER* cipherInfo = EVP_aes_256_cbc();
	int iklen = EVP_CIPHER_key_length(cipherInfo);
	int ivlen = EVP_CIPHER_iv_length(cipherInfo);
	Crypto::PBKDF2_derive_key_iv(masterKey, salt, Key, iklen, IV, ivlen);

	salt = _salt.ToStdString();

	unsigned char plain[128];
	plain_text = Crypto::decrypt(Crypto::hexStringToChar(cipher_text), cipher_text.length() / 2, Key, IV, plain);
}
Password::~Password()
{
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
