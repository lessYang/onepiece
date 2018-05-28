#include <stdio.h>
#include <stdlib.h>


#include <string>
#include <iostream>


#include "base/crypto/aes.h"
#include "base/stringpiece.h"
#include "base/encoding/base64.h"

int main(int /*argc*/, char ** /*argv*/) {
    using namespace base;

    std::string input ("for testing, aaaaes");
    std::string output;
    StringPiece key("1234567890123456");

    int ret = AES::aesCBC16Encypt(input, key, &output);
    std::cout << "Encrypt=" << ret << "\n";

    std::string org_output;
    
    ret = AES::aesCBC16Decrypt(output, key, &org_output);

    std::cout << "Decrypt=" << ret << "\n";
    std::cout << "-->" << input << "\n";
    std::cout << "-->" << org_output << "\n";
    
    std::string b64;
    base::Base64Encode(output, &b64);

    std::cout << b64 << "\n";


    return 0;
}
