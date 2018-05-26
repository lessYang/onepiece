#include "base/util.h"

std::string string_to_hex(const pcrecpp::StringPiece &input) {
    static const char* const lut = "0123456789ABCDEF";
    std::string output;
    output.reserve(2 * input.size());
    for (int i = 0; i < input.size(); ++i) {
        const unsigned char c = input.data()[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}
