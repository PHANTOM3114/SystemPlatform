#pragma once

#include <openssl/evp.h>
#include <vector>
#include <string>

class CryptoManager
{
private:

    EVP_CIPHER_CTX* encryptCtx;
    EVP_CIPHER_CTX* decryptCtx;
    unsigned char key[32];     // AES-256

public:

    CryptoManager();
    ~CryptoManager();

    std::vector<unsigned char> encrypt(const std::string& plaintext, std::vector<unsigned char>& iv, std::vector<unsigned char>& tag);
    std::string decrypt(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& iv, const std::vector<unsigned char>& tag);

};