#pragma once

#include <string>
#include <sodium.h>

#include "Base64.hpp"
#include "Utils.hpp"

namespace aesdemo {
    class Crypto {
    public:
        static std::string encrypt(unsigned char *key, unsigned char *iv, std::string input);

    private:
        unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
        unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
        std::string ciphertext;
    };
}