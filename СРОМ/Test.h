#pragma once
#include <iostream>
#include <string>

using namespace std;

bool g_any_test_failed = false;

template<typename T, typename U>
void ASSERT_EQUAL(const T& actual, const U& expected, const std::string& test_name) 
{
    if (actual == expected) 
    {
    }
    else {
        cerr << "? FAILED: " <<  endl;
        g_any_test_failed = true;
    }
}
