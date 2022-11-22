#include <iostream>
#include <cstdint>
#include <list>
#include <iterator>
#include <functional>
#include <memory>


class Singleton
{
private:
    Singleton()
    {
        std::cout << "Created\n";
    };

    inline static std::shared_ptr<Singleton> object{nullptr};

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::shared_ptr<Singleton> get_object();

    void print() const
    {
        std::cout << "Singleton\n";
    };

    ~Singleton()
    {
        std::cout << "Destroyed\n";
    };
};

// std::shared_ptr<Singleton> Singleton::object = nullptr;

std::shared_ptr<Singleton> Singleton::get_object()
{
    if (!object)
    {
        object = std::shared_ptr<Singleton>(new Singleton());
    }
    return object;
};


int main()
{
    Singleton::get_object()->print();
    Singleton::get_object()->print();
    Singleton::get_object()->print();

    return 0;
};
