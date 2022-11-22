#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class ConcreteVisitable1;
class ConcreteVisitable2;

class Visitor 
{
public:
    virtual void visit(ConcreteVisitable1& visitable) = 0;
    virtual void visit(ConcreteVisitable2& visitable) = 0;
    virtual ~Visitor() = default;
};

class Visitable
{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Visitable() = default;
};

class ConcreteVisitable1 : public Visitable
{
public:
    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    };
    virtual ~ConcreteVisitable1() = default;
};

class ConcreteVisitable2 : public Visitable
{
public:
    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    };
    virtual ~ConcreteVisitable2() = default;
};

class ConcreteVisitor : public Visitor
{
public:
    void visit(ConcreteVisitable1& visitable) override
    {
        // do something with visitable
        std::cout << "Visited first\n";
    };
    void visit(ConcreteVisitable2& visitable) override
    {
        // do something with visitable
        std::cout << "Visited second\n";
    };
    virtual ~ConcreteVisitor() = default;
};

int main()
{
    std::vector<std::shared_ptr<Visitable>> vec;
    vec.push_back(std::make_shared<ConcreteVisitable1>());
    vec.push_back(std::make_shared<ConcreteVisitable2>());

    ConcreteVisitor visitor;

    for (auto& elem : vec)
    {
        elem->accept(visitor);
    }

    return 0;
};
