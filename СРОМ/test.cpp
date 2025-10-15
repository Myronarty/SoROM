#include "Test.h"
#include "Numb.h"

void test_simple_addition() 
{
    Number A("100");
    Number B("250");
    Number Expected("350");
    ASSERT_EQUAL(A + B, Expected, "Simple Addition Test");
}

void test_addition_with_carry() 
{
    Number A("FFFFFFFF");
    Number B("1");
    Number Expected("100000000");
    ASSERT_EQUAL(A + B, Expected, "Addition with Carry Test");
}

void test_multiplication() 
{
    Number A("1000");
    Number B("10");
    Number Expected("10000");
    ASSERT_EQUAL(A * B, Expected, "Multiplication Test");
}
