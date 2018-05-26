#include "gtest/gtest.h"

#include <string.h>
#include <memory>
#include "base/crypto/md5.h"
#include "base/encoding/hex.h"
#include <iostream>

TEST(MD5, md5) {
    MD5_CTX * ctx = new MD5_CTX;
    MD5_Init(ctx);

    const char * data = "This is a test 1123";

    MD5_Update(ctx, (const void *)data, strlen(data));
    unsigned char output[16] = {'\0'};
    MD5_Final(output, ctx);

    pcrecpp::StringPiece sp((const char *)output, 16);
    std::string out = Hex::encodeToString(sp);

    EXPECT_EQ("8a2804640a7072ea114a71a580c77a32", out);
}
