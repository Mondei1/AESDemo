#pragma once

#include <iostream>
#include <cryptopp/secblock.h>

#include "Base64.hpp"
#include "Utils.hpp"

namespace aesdemo {
    class Crypto {
    public:
        Crypto(bool useKDF);
        enum class ModeOfOperation {
            cbc,
            ecb
        };
        std::string Encrypt(ModeOfOperation mode, std::string key, const std::string& input, std::string iv = "");
        std::string Decrypt(ModeOfOperation mode, std::string key, const std::string& input, std::string iv = "");

    private:
        bool useKDF;

        void CheckInput(const std::string& key, const std::string& iv, ModeOfOperation mode);
        void DoKDF(const std::string& input, CryptoPP::SecByteBlock &forBlock);
    };
}