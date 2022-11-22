#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <cstddef>
#include <initializer_list>

template<typename T>
class List
{
private:
    template<typename T>
    class Node
    {
    private:
        T value {};
        Node<T>* next {};

    public:
        Node<T>() = default;
        Node<T>(T _value) : value(_value), next(nullptr) {};
        void set_next(Node<T>* _next) { next = _next; };
        Node<T>* get_next() { return next; };
        T get_value() { return value; };
    };


    Node<T>* first {nullptr};
    int32_t size {0};

public:
    List<T>() = default;
    List<T>(int32_t _size) : List<T>()
    {
        if (_size < 0)
        {
            throw std::runtime_error("Wrong size of list");
        }

        size = _size;
        if (size != 0)
        {
            first = new Node<T> {};
        }
        auto temp {first};
        for (std::size_t i {1}; i < size; i++)
        {
            temp->set_next(new Node<T> {});
            temp = temp->get_next();
        }
    };
    List<T>(const std::initializer_list<T> &list) : List<T>()
    {
        size = static_cast<int32_t>(list.size());

        auto iter = list.begin();
        first = new Node<T> {*iter};
        ++iter;
            
        auto temp = first;
        for (std::size_t i = 1; i < size; i++)
        {
            temp->set_next(new Node<T> {*iter});
            temp = temp->get_next();
            ++iter;
        }
    };
    List<T>(const List<T>&) = delete;
    List<T>& operator=(const List<T>&) = delete;
    List<T>(List<T>&& list)
    {
        first = list.first;
        size = list.size;

        list.first = nullptr;
        list.size = 0;
    }
    List<T>& operator=(List<T>&& list)
    {
        if (this == &list)
        {
            return *this;
        }

        auto temp {first};
        while (temp)
        {
            auto next {temp->get_next()};
            delete temp;
            temp = next;
        }

        first = list.first;
        size = list.size;

        list.first = nullptr;
        list.size = nullptr;

        return *this;
    }
    ~List<T>()
    {
        auto temp {first};
        while (temp)
        {
            auto next {temp->get_next()};
            delete temp;
            temp = next;
        }
        size = 0;
    };

    void insert(int32_t position, const T& value)
    {
        if (position < 0 || position > size)
        {
            throw std::runtime_error("Wrong position");
        }

        Node<T>* node_value {new Node<T> {value}};
        Node<T>* place {first};
        Node<T>* prev {nullptr};
        for (std::size_t i {0}; i < position; i++)
        {
            prev = place;
            place = place->get_next();
        }
        if (prev)
        {
            prev->set_next(node_value);
        }
        else
        {
            first = node_value;
        }
        node_value->set_next(place);
        size++;
    };

    void push_front(const T& value)
    {
        Node<T> *node_value {new Node<T> {value}};
        node_value->set_next(first);
        first = node_value;
        size++;
    };

    T pop_front()
    {
        T value = first->get_value();

        auto temp = first;
        first = first->get_next();
        delete temp;

        size--;
        return value;
    };
};

#endif