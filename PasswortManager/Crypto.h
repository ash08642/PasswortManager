#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <sha.h>
#include <evp.h>
#include <openssl/kdf.h>
#include <iostream>
#include <random>

namespace Crypto
{
    std::string Hash_SHA256(const std::string plain_text, int iterations, std::string salt);
    std::string PBKDF2_derive_key_iv(const std::string& pass, const std::string& salt, int size, unsigned char* key, unsigned int key_len, unsigned char* iv, unsigned int iv_len);
    std::string generateSalt();

    std::string charToHexString(const unsigned char* digest, unsigned int digest_len);
};

