#include <string>

namespace aesdemo {
    class Utils {
    public:
        static std::string stringToHex(char* input);
        static std::string convertToString(char* a, int size);
    };
}