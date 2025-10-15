#include "Test.h"
#include <iostream>

void test_simple_addition();
void test_addition_with_carry();
void test_multiplication();

int main() 
{
    test_simple_addition();
    test_addition_with_carry();
    test_multiplication();

    if (g_any_test_failed) {
        std::cout << "\n Some tests failed." << std::endl;
        return 1;
    }
    else {
        std::cout << "All tests passed successfully!" << std::endl;
        return 0;
    }
}
