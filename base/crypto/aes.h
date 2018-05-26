#ifndef ONEPIECE_BASE_CRYPTO_AES_H_
#define ONEPIECE_BASE_CRYPTO_AES_H_

#include "pcre_stringpiece.h"

#include <string>
/*
enum class AESError {
   SUCCESS = 0,
   UNSUPPORTED_MODE = -1,
   UNSUPPORTED_DIRECTION = -2,
   UNSUPPORTED_KEY_LENGTH = -3,
   RIJNDAEL_BAD_KEY = -4,
   NOT_INITIALIZED = -5,
   RIJNDAEL_BAD_DIRECTION = -6,
   RIJNDAEL_CORRUPTED_DATA = -7,
   BADPARMA = -8
};
*/

class AES {
public:
    AES() = default;
    ~AES() = default;
    static int aesCBC16Encypt(const pcrecpp::StringPiece& input, 
                            const pcrecpp::StringPiece& key,
                            std::string* output);

    static int aesCBC16Decrypt(const pcrecpp::StringPiece& input,
                             const pcrecpp::StringPiece& key,
                             std::string* output);
    
    static int aesCBC32Encypt(const pcrecpp::StringPiece& input, 
                              const pcrecpp::StringPiece& key,
                              std::string* output);
    static int aesCBC32Decrypt(const pcrecpp::StringPiece& input,
                               const pcrecpp::StringPiece& key,
                               std::string* output);
};

#endif  // ONEPIECE_BASE_CRYPTO_AES_H_

