#include <string>

namespace aesdemo {
    class Utils {
    public:
        static std::string BinaryToHex(const uint8_t* binary,
                                                size_t binaryLength);
        static int HexToBinary(char* input, uint8_t* output);
        static std::string ConvertToString(const char* a, int size);
        static std::string RandomString(std::size_t length);
        static uint8_t CharToUint(char ch);
    };
}