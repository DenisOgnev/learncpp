#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Worker
{
public:
    virtual ~Worker() = default;
    virtual void do_something() const = 0;
};

class ConcreteWorker : public Worker
{
public:
    ConcreteWorker() = default;
    virtual ~ConcreteWorker() = default;
    void do_something() const override
    {
        std::cout << "Concrete is working\n";
    };
};

class AnotherWorker : public Worker
{
public:
    AnotherWorker() = default;
    virtual ~AnotherWorker() = default;
    void do_something() const override
    {
        std::cout << "Another is working\n";
    };
};

class Connector
{
public:
    virtual ~Connector() = default;
    virtual void work(std::shared_ptr<Worker>) const = 0; 
};

class ConcreteConnector : public Connector
{
public:
    ConcreteConnector() = default;
    virtual ~ConcreteConnector() = default;
    void work(std::shared_ptr<Worker> worker) const override
    {
        worker->do_something();
    }
};

int main()
{
    auto worker1{std::make_shared<ConcreteWorker>()};
    auto worker2{std::make_shared<AnotherWorker>()};

    auto connector{std::make_shared<ConcreteConnector>()};

    connector->work(worker1);
    connector->work(worker2);

    return 0;
};
