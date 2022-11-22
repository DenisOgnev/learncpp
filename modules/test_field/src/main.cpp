#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>
#include <test.hpp>
#include <memory>
#include <vector>

void test(int32_t *ptr)
{
    std::cout << *ptr << "\n";
};

void test2(std::shared_ptr<int32_t> ptr)
{
    std::cout << *ptr << "\n";
};

std::unique_ptr<int32_t> test3(std::unique_ptr<int32_t> ptr)
{
    std::cout << *ptr << "\n";
    return ptr;
};

int main()
{
    int32_t *dumbptr{new int{10}};
    std::shared_ptr<int32_t> shptr{std::make_shared<int32_t>(15)};
    std::unique_ptr<int32_t> unptr{std::make_unique<int32_t>(20)};

    test(dumbptr);
    test(shptr.get());
    test(unptr.get());
    std::cout << "\n";

    test2(std::make_shared<int32_t>(*dumbptr));
    test2(shptr);
    // test2(std::move(unptr));
    std::cout << "\n";

    test3(std::make_unique<int32_t>(*dumbptr));
    // test3(std::move(shptr));
    unptr = test3(std::move(unptr));

    delete dumbptr;
    return 0;
};
