#include <string>

namespace aesdemo {
    class Utils {
    public:
        static std::string stringToHex(const char* input);
        static std::string convertToString(const char* a, int size);
    };
}