#include "gtest/gtest.h"

#include <string.h>
#include <memory>
#include "base/encoding/md5.h"
#include "base/util.h"
#include <iostream>

TEST(MD5, md5) {
    MD5_CTX * ctx = new MD5_CTX;
    MD5_Init(ctx);

    const char * data = "This is a test 1123";

    MD5_Update(ctx, (const void *)data, strlen(data));
    unsigned char output[16] = {'\0'};
    MD5_Final(output, ctx);

    pcrecpp::StringPiece sp((const char *)output, 16);
    std::string out = string_to_hex(sp);

    EXPECT_EQ("8A2804640A7072EA114A71A580C77A32", out);
}

