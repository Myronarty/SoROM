#include "gtest/gtest.h"
#include "Numb.h"

TEST(NumberArithmetic, Addition) {
    Number A1("1000200030004000");
    Number B1("5000600070008000");
    Number expected1("60008000A000C000");
    EXPECT_EQ(A1 + B1, expected1);

    Number A2("FFFFFFFF");
    Number B2("1");
    Number expected2("100000000");
    EXPECT_EQ(A2 + B2, expected2);

    Number A3("FEDCBA9876543210FEDCBA9876543210");
    Number B3("0");
    EXPECT_EQ(A3 + B3, A3);

    std::string max_hex = "";
    for (int i = 0; i < 512; ++i) {
        max_hex += "F";
    }
    Number MaxValue(max_hex);
    Number One("1");

    Number expected4("0");
    EXPECT_EQ(MaxValue + One, expected4);
}