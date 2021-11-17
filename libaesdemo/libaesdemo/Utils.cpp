#include <iostream>
#include <ios>
#include <iomanip>
#include "Utils.hpp"

std::string aesdemo::Utils::stringToHex(char* input) {
    std::stringstream hex;

    for (int i = 0; i < sizeof(input); i++) {
        hex << std::hex << int(input[i]);
    }

    return hex.str();
}

std::string aesdemo::Utils::convertToString(char *a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}