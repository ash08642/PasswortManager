#include "Crypto.h"

std::string Crypto::Hash_SHA256(const std::string plain_text, int iterations, std::string salt)
{
    unsigned char message = (unsigned char)(plain_text + salt).c_str();
    unsigned int message_len = (plain_text + salt).length();

    unsigned char* digest_buffer = new unsigned char[EVP_MD_size(EVP_sha256())];
    unsigned int digest_bbuffer_len = EVP_MD_size(EVP_sha256());

    unsigned char* digest;
    unsigned int digest_len = 0;

    EVP_MD_CTX* mdctx;

    if ((mdctx = EVP_MD_CTX_new()) == NULL)
        return "Error creating mdctx";

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
        return "Error initializing mdctx";

    if (1 != EVP_DigestUpdate(mdctx, &message, message_len))
        return "Error updating mdctx";

    if ((digest = (unsigned char*)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
        return "Error in size of";

    if (1 != EVP_DigestFinal_ex(mdctx, digest, &digest_len))
        return "Error finalizing mdctx";

    EVP_MD_CTX_free(mdctx);

    for (size_t i = 1; i < iterations; i++)
    {
        memcpy(&digest_buffer[0], &digest[0], digest_len * sizeof(unsigned char));

        if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
            return "Error initializing mdctx";

        if (1 != EVP_DigestUpdate(mdctx, digest_buffer, digest_bbuffer_len))
            return "Error updating mdctx";

        if ((digest = (unsigned char*)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
            return "Error in size of";

        if (1 != EVP_DigestFinal_ex(mdctx, digest, &digest_len))
            return "Error finalizing mdctx";
    }

    std::stringstream ss;
    for (unsigned int i = 0; i < digest_len; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    delete[] digest_buffer;

    return ss.str();
}

std::string Crypto::PBKDF2_derive_key_iv(
    const std::string& pass,
    const std::string& salt,
    int size, unsigned char* key, unsigned int key_len,
    unsigned char* iv, unsigned int iv_len
)
{
    EVP_KDF* kdf;
    EVP_KDF_CTX* kctx = NULL;
    unsigned char derived[32];
    OSSL_PARAM params[4], * p = params;

    if ((kdf = EVP_KDF_fetch(NULL, "pbkdf2", NULL)) == NULL)
    {
        return "error at KDF_fetch";
    }
    kdf = EVP_KDF_fetch(NULL, "pbkdf2", NULL);
    kctx = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kctx == NULL)
    {
        return "error at KDF_CTX_new";
    }
    
    /* Build up the parameters for the derivation */
    *p++ = OSSL_PARAM_construct_utf8_string("digest", (char*)"sha256", (size_t)7);
    *p++ = OSSL_PARAM_construct_octet_string("salt", (void*)salt.c_str(), (size_t)4);
    *p++ = OSSL_PARAM_construct_octet_string("key", (void*)pass.c_str(), (size_t)6);
    *p++ = OSSL_PARAM_construct_octet_string("info", "label", (size_t)5);
    *p = OSSL_PARAM_construct_end();
    if (EVP_KDF_CTX_set_params(kctx, params) <= 0) {
        return "EVP_KDF_CTX_set_params";
    }

    /* Do the derivation */
    if (EVP_KDF_derive(kctx, derived, sizeof(derived), NULL) <= 0) {
        return "EVP_KDF_derive";
    }

    /* Use the 32 bytes as a Key and IV */
    const unsigned char* key = derived + 0;
    const unsigned char* iv = derived + 16;

    EVP_KDF_CTX_free(kctx);
}

std::string Crypto::generateSalt()
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string salt = "";

    for (std::size_t i = 0; i < 8; ++i)
    {
        salt += CHARACTERS[distribution(generator)];
    }

    return salt;
}

std::string Crypto::charToHexString(const unsigned char* digest, unsigned int digest_len)
{
    std::stringstream ss;
    for (unsigned int i = 0; i < digest_len; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    delete[] digest_buffer;

    return ss.str();
}
