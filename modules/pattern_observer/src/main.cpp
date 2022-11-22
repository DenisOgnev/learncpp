#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>

class Subscriber
{
public:
    virtual ~Subscriber() = default;
    virtual void update(const std::string&) const = 0;
};

class ConcreteSubscriber : public Subscriber
{
    std::string name{};
public:
    ConcreteSubscriber() = default;
    ConcreteSubscriber(const std::string& _name) : name{_name} {};
    virtual ~ConcreteSubscriber() = default;

    void update(const std::string& data) const override
    {
        std::cout << "Updated from " + name << " by " << data << "\n";
    };
};

class AnotherSubscriber : public Subscriber
{
    int32_t id {};
public:
    AnotherSubscriber() = default;
    AnotherSubscriber(int32_t _id) : id{_id} {};
    virtual ~AnotherSubscriber() = default;

    void update(const std::string& data) const override
    {
        std::cout << "Updated from id = " << id << " by " << data << "\n";
    };
};

class Notifier
{
public:
    virtual ~Notifier() = default;
    virtual void add_subscriber(std::shared_ptr<Subscriber>) = 0;
    virtual void remove_subscriber(std::shared_ptr<Subscriber>) = 0;
    virtual void notify_all() const = 0;
};

class ConcreteNotifier : public Notifier
{
private:
    std::string name{};
    std::list<std::shared_ptr<Subscriber>> subscribers{};

public:
    ConcreteNotifier() = default;
    ConcreteNotifier(const std::string _name) : name{_name} {};
    virtual ~ConcreteNotifier() = default;

    void add_subscriber(std::shared_ptr<Subscriber> subscriber) override
    {
        subscribers.push_back(subscriber);
    };

    void remove_subscriber(std::shared_ptr<Subscriber> subscriber) override
    {
        subscribers.remove(subscriber);
    };

    void notify_all() const override
    {
        for (const auto &subscriber : subscribers)
        {
            subscriber->update(name);
        }
    };
};

int main()
{
    auto sub1{std::make_shared<ConcreteSubscriber>("Denis")};
    auto sub2{std::make_shared<AnotherSubscriber>(1)};
    auto sub3{std::make_shared<ConcreteSubscriber>("Ognev")};

    std::shared_ptr<Notifier> notifier{std::make_shared<ConcreteNotifier>("DenisNotifier")};
    notifier->add_subscriber(sub1);
    notifier->add_subscriber(sub2);
    notifier->add_subscriber(sub3);

    notifier->notify_all();
    

    return 0;
};
