#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Implementation
{
public:
    virtual void method1() = 0;
    virtual void method2() = 0;
    virtual ~Implementation() = default;
};

class ConcreteImplementation : public Implementation
{
public:
    void method1() override
    {
        std::cout << "method1\n";
    };
    void method2() override
    {
        std::cout << "method2\n";
    };
    virtual ~ConcreteImplementation() = default;
};

class Abstraction
{
protected:
    std::shared_ptr<Implementation> implementation;
public:
    Abstraction() = default;
    Abstraction(std::shared_ptr<Implementation> _implementation) : implementation{_implementation} {};
    virtual ~Abstraction() = default;
    virtual void do_work()
    {
        implementation->method1();
    };
    void set_implementation(std::shared_ptr<Implementation> _implementation)
    {
        implementation = _implementation;
    };
};

class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction() = default;
    ExtendedAbstraction(std::shared_ptr<Implementation> _implementation) : Abstraction{_implementation} {};
    virtual ~ExtendedAbstraction() = default;
    void do_work() override
    {
        implementation->method1();
        implementation->method2();
    };
};

int main()
{
    std::shared_ptr<Implementation> implementation{std::make_shared<ConcreteImplementation>()};
    std::unique_ptr<Abstraction> abstraction1{std::make_unique<Abstraction>(implementation)};
    std::unique_ptr<Abstraction> abstraction2{std::make_unique<ExtendedAbstraction>(implementation)};

    abstraction1->do_work();
    abstraction2->do_work();

    return 0;
};
