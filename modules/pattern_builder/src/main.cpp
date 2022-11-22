#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Product
{
    std::string test{};
public:
    void append_string(const std::string& str)
    {
        test += str;
    };
    void print()
    {
        std::cout << test << "\n";
    };
};

class Builder
{
public:
    virtual void build_str(const std::string& str) = 0;
    virtual ~Builder() = default;
};

class ConcreteBuilder : public Builder
{
    std::unique_ptr<Product> product;
public:
    ConcreteBuilder() : product{std::make_unique<Product>()} {};
    void build_str(const std::string& str) override
    {
        product->append_string(str);
    };
    virtual ~ConcreteBuilder() = default;
    std::unique_ptr<Product> get_product()
    {
        if (!product) throw std::runtime_error("Attempt to return an empty product");
        auto result{std::move(product)};
        reset();
        return result;
    };
    void reset()
    {
        product = std::make_unique<Product>();
    };
};

int main()
{
    std::unique_ptr<Product> product;
    {
        ConcreteBuilder builder;

        builder.build_str("123, ");
        builder.build_str("test");

        product = builder.get_product();
    }

    product->print();

    return 0;
};
