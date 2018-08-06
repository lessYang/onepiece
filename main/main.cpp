#include <stdio.h>
#include <stdlib.h>


#include <string>
#include <iostream>

#include <unistd.h>

#include "base/crypto/aes.h"
#include "base/stringpiece.h"
#include "base/encoding/base64.h"

#include "base/time/time.h"
#include "base/encoding/ini.h"

int main(int /*argc*/, char ** /*argv*/) {
    using namespace base;

    //auto start = Time::NowNano();
    auto start = Time::NowMilli();
    sleep(1);
    //auto end = Time::NowNano();
    auto end = Time::NowMilli();

    std::cout << (end - start) << "ms\n";


    std::shared_ptr<INI> ini (new INI);
    if (ini->parse("1.ini") != 0) { return 0; }

    int port;
    std::string host;
    int timeout;

    if (ini->getValue(port, "port")) {
        std::cout << "port default session = " << port << "\n";
    }
    if (ini->getValue(port, "port", "ap")) {
        std::cout << "port ap session = " << port << "\n";
    }

    if (ini->getValue(host, "host")) {
        std::cout << "host default session = " << host << "\n";
    }
    if (ini->getValue(host, "host", "ap")) {
        std::cout << "host ap session = " << host << "\n";
    }

    if (ini->getValue(timeout, "timeout")) {
        std::cout << "timeout default session = " << timeout << "\n";
    }
    if (ini->getValue(timeout, "timeout", "ap")) {
        std::cout << "timeout ap session = " << timeout << "\n";
    }

#if 0
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
#endif

    return 0;
}
