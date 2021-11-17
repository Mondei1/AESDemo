#include <iostream>
#include <cstring>
#include "Crypto.hpp"

std::string aesdemo::Crypto::encrypt(unsigned char *key, unsigned char *iv, std::string input) {
    size_t buf_unpadded_len = strlen(reinterpret_cast<const char *>(key));
    size_t buf_padded_len;
    size_t block_size = 32;

    //int padAction = sodium_pad(&buf_padded_len, key, buf_unpadded_len, block_size, sizeof key);

    if (1 != 0) {
        std::cerr << "Couldn't apply padding to key \"" << key << "\" (buf_unpadded_len = " << buf_unpadded_len << "; buf_padded_len = " << buf_padded_len << ")" << std::endl;
        return "";
    }

    std::cout << base64_encode(Utils::convertToString(reinterpret_cast<char *>(buf_padded_len), sizeof(key))) << std::endl;

    return "worked";
}