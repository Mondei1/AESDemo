#pragma once

#include <iostream>
#include <tinyaes/aes.hpp>

extern "C" {
    #include <tinypkcs/pkcs7_padding.h>
}

#include "Base64.hpp"
#include "Utils.hpp"

namespace aesdemo {
    class Crypto {
    public:
        enum class ModeOfOperation {
            cbc,
            ecb
        };
        static std::string encrypt(ModeOfOperation mode, unsigned char *key, std::string input, unsigned char *iv = nullptr);

    private:
        std::string ciphertext;
    };
}