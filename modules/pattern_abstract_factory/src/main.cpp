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
        std::cout << "Product 1\n";
    };
    virtual ~ConcreteProduct1() = default;
};

class ConcreteProduct2 : public Product
{
public:
    void method() const override
    {
        std::cout << "Product 2\n";
    };
    virtual ~ConcreteProduct2() = default;
};

class Element
{
public:
    virtual void method() const = 0;
    virtual ~Element() = default;
};

class ConcreteElement1 : public Element
{
public:
    void method() const override
    {
        std::cout << "Element 1\n";
    };
    virtual ~ConcreteElement1() = default;
};

class ConcreteElement2 : public Element
{
public:
    void method() const override
    {
        std::cout << "Element 2\n";
    };
    virtual ~ConcreteElement2() = default;
};

class Factory
{
public:
    virtual std::unique_ptr<Product> create_product() = 0;
    virtual std::unique_ptr<Element> create_element() = 0;
    virtual ~Factory() = default;
};

class ConcreteFactory1 : Factory
{
public:
    std::unique_ptr<Product> create_product() override
    {
        return std::make_unique<ConcreteProduct1>();
    };
    std::unique_ptr<Element> create_element() override
    {
        return std::make_unique<ConcreteElement1>();
    };
    virtual ~ConcreteFactory1() = default;
};

class ConcreteFactory2 : Factory
{
public:
    std::unique_ptr<Product> create_product() override
    {
        return std::make_unique<ConcreteProduct2>();
    };
    std::unique_ptr<Element> create_element() override
    {
        return std::make_unique<ConcreteElement2>();
    };
    virtual ~ConcreteFactory2() = default;
};


int main()
{
    auto fabric1{std::make_unique<ConcreteFactory1>()};
    auto fabric2{std::make_unique<ConcreteFactory2>()};

    std::vector<std::unique_ptr<Product>> products;
    products.push_back(fabric1->create_product());
    products.push_back(fabric2->create_product());
    products.push_back(fabric1->create_product());

    for (const auto& product : products)
    {
        product->method();
    }

    std::vector<std::unique_ptr<Element>> elements;
    elements.push_back(fabric1->create_element());
    elements.push_back(fabric2->create_element());
    elements.push_back(fabric1->create_element());

    for (const auto& element : elements)
    {
        element->method();
    }

    return 0;
};
