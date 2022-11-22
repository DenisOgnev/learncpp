#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Printer
{
public:
    virtual ~Printer() = default;
    virtual void print() const = 0;
};

class ConcretePrinter : public Printer
{
public:
    ConcretePrinter() = default;
    virtual ~ConcretePrinter() = default;

    void print() const override
    {
        std::cout << "Printed\n";
    };
};

class DifferentPrinter
{
public:
    virtual ~DifferentPrinter() = default;
    virtual void different_print() const = 0;
};

class Adapter : public DifferentPrinter, public ConcretePrinter
{
public:
    Adapter() = default;
    virtual ~Adapter() = default;
    void different_print() const override
    {
        print();
    };
};

class SecondAdapter : DifferentPrinter
{
    ConcretePrinter printer {};
public:
    SecondAdapter() = default;
    virtual ~SecondAdapter() = default;
    void different_print() const override
    {
        printer.print();
    };
};

int main()
{
    auto adapter{std::make_shared<Adapter>()};
    adapter->different_print();

    auto second_adapter{std::make_shared<SecondAdapter>()};
    second_adapter->different_print();

    return 0;
};
