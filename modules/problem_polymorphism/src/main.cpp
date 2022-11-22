#include <iostream>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>


class Base
{
protected:
    const int32_t value {};
public:
    Base() = default;
    Base(int32_t _value) : value(_value) { };
    virtual ~Base() 
    {
        std::cout << "~Base()\n";
    };

    virtual void print() const
    {
        std::cout << value << "\n";
    };
};


class Derived final : public Base
{
protected:
    const std::string name {};
public:
    Derived() = default;
    Derived(int32_t _value, const std::string& _name) : Base(_value), name(_name) { };
    ~Derived() override
    {
        std::cout << "~Derived()\n"; 
    };
    
    void print() const override
    {
        std::cout << value << " " << name << "\n";
    };
};



int main()
{
    std::vector<std::shared_ptr<Base>> vector;

    vector.push_back(std::make_shared<Base>(1));
    vector.push_back(std::make_shared<Derived>(2, "123"));
    vector.push_back(std::make_shared<Derived>(3, "456"));

    for (const auto& elem : vector)
    {
        elem->print();
    }


    return 0;
};
