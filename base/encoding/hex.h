#ifndef ONEPIECE_BASE_ENCODING_HEX_
#define ONEPIECE_BASE_ENCODING_HEX_

#include <string>

#include "pcre_stringpiece.h"

class Hex {
public:
    Hex() = default;
    ~Hex() = default;

    /**
     * @brief encodeToString returns the hexadecimal encoding of input
     * @param input
     * @return
     */
    static std::string encodeToString(const pcrecpp::StringPiece& input);

    /**
     * @brief decodeString returns the string represented by the hexadecimal string input
     * @param input
     * @param output
     * @return
     */
    static bool decodeString(const pcrecpp::StringPiece& input, std::string* output);
    static const char* const hexTable_;
};

#endif  // ONEPIECE_BASE_ENCODING_HEX_
