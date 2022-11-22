#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Product
{
public:
    virtual void method() const = 0;
    virtual ~Product() = default;
};

class ConcreteProduct1 : public Product
{
public:
    void method() const override
    {
        std::cout << "Concrete product 1\n";
    };
    virtual ~ConcreteProduct1() = default;
};

class ConcreteProduct2 : public Product
{
public:
    void method() const override
    {
        std::cout << "Concrete product 2\n";
    };
    virtual ~ConcreteProduct2() = default;
};

class Creator
{
public:
    virtual std::unique_ptr<Product> create() = 0;
    virtual ~Creator() = default;
};

class ConcreteCreator1 : public Creator
{
public:
    std::unique_ptr<Product> create()
    {
        return std::make_unique<ConcreteProduct1>();
    };
    virtual ~ConcreteCreator1() = default;
};

class ConcreteCreator2 : public Creator
{
public:
    std::unique_ptr<Product> create()
    {
        return std::make_unique<ConcreteProduct2>();
    };
    virtual ~ConcreteCreator2() = default;
};

int main()
{
    ConcreteCreator1 creator1;
    ConcreteCreator2 creator2;

    std::vector<std::unique_ptr<Product>> vec{};
    vec.push_back(creator1.create());
    vec.push_back(creator2.create());
    vec.push_back(creator2.create());

    for (const auto& elem : vec)
    {
        elem->method();
    }

    return 0;
};
