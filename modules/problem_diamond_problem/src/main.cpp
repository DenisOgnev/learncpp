#include <iostream>
#include <cstdint>


class A
{
public:
    A()
    {
        std::cout << "A()\n";
    };
};

class B : virtual public A
{
public:
    B() : A()
    {
        std::cout << "B()\n";
    };
};

class C : virtual public A
{
public:
    C() : A()
    {
        std::cout << "C()\n";
    };
};

class D : public B, C
{
public:
    D() : B(), C()
    {
        std::cout << "D()\n";
    };
};


int main()
{
    D d {};

    return 0;
};
