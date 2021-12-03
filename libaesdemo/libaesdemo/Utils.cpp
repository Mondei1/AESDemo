#include <iostream>
#include <ios>
#include <iomanip>
#include "Utils.hpp"

std::string aesdemo::Utils::stringToHex(const char* input) {
    std::stringstream hex;

    for (int i = 0; i < sizeof(input); i++) {
        hex << std::hex << int(input[i]);
    }

    return hex.str();
}

std::string aesdemo::Utils::convertToString(const char *a, int size) {
    return std::string(a, size);
}