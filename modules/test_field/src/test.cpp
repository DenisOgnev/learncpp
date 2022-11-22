#include <test.hpp>
#include <iostream>
#include <string>


void test()
{
    int32_t first {123};
    int32_t second {std::move(first)};

    std::cout << first << " " << second << "\n";

    std::cout << "test1\n";
};