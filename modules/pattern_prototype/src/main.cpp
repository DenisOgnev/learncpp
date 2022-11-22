#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Prototype
{
protected:
    std::string data{""};
public:
    Prototype() = default;
    Prototype(std::string _data) : data{_data} {};
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() const
    {
        std::cout << data << "\n";
    };
    virtual ~Prototype() = default;
};

class ConcreteProrotype1 : public Prototype
{
int32_t field{0};
public:
    ConcreteProrotype1() : Prototype{} {};
    ConcreteProrotype1(std::string _data, int32_t _field) : Prototype{_data}, field{_field} {};
    std::unique_ptr<Prototype> clone() const override
    {
        return std::make_unique<ConcreteProrotype1>(*this);
    };
    void print() const override
    {
        std::cout << data << " " << field << "\n";
    };
    virtual ~ConcreteProrotype1() = default;
};

class ConcreteProrotype2 : public Prototype
{
float field{0.0f};
public:
    ConcreteProrotype2() : Prototype{} {};
    ConcreteProrotype2(std::string _data, float _field) : Prototype{_data}, field{_field} {};
    std::unique_ptr<Prototype> clone() const override
    {
        return std::make_unique<ConcreteProrotype2>(*this);
    };
    void print() const override
    {
        std::cout << data << " " << field << "\n";
    };
    virtual ~ConcreteProrotype2() = default;
};


int main()
{
    ConcreteProrotype1 prototype1("Temp", 123);
    ConcreteProrotype2 prototype2("Temp2", 123.2f);

    auto copy1{prototype1.clone()};
    auto copy2{prototype2.clone()};

    copy1->print();
    copy2->print();

    return 0;
};
