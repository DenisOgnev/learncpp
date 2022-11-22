#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>
#include <initializer_list>

template<typename T>
class MyVector
{
private:
    T* data {nullptr};
    std::size_t size {0};
    std::size_t capacity {0};
    std::size_t capacity_increase {3};
public:
    MyVector<T>() = default;
    MyVector<T>(int32_t _size)
    {
        if (_size < 1)
        {
            throw std::runtime_error("Wrong size of vector");
        }
        size = static_cast<std::size_t>(_size);
        capacity = static_cast<std::size_t>(_size) + capacity_increase;
        data = new T[capacity] {};
    }
    MyVector<T>(int32_t _size, const T& value) : MyVector<T>(_size)
    { 
        fill(value); 
    }
    MyVector<T>(const std::initializer_list<T>& list) : MyVector<T>(static_cast<int32_t>(list.size()))
    {
        std::size_t i {0};
        for (const auto &elem : list)
        {
            data[i] = elem;
            ++i;
        }
    }
    MyVector<T>(const MyVector<T>& vector)
    {
        size = vector.size;
        capacity = vector.capacity;
        data = new T[capacity] {};

        for (std::size_t i {0}; i < size; i++)
        {
            data[i] = vector.data[i];
        }
    }
    MyVector<T>(MyVector<T>&& vector) noexcept : data(vector.data), size(vector.size), capacity(vector.capacity)
    {
        vector.data = nullptr;
        vector.size = 0;
        vector.capacity = 0;
    }
    ~MyVector() { delete[] data; }

    std::size_t get_size() { return size; }
    std::size_t get_capacity() { return capacity; }
    T& operator[](int32_t index) { return data[index]; }
    T* begin() { return data; }
    T* end() { return data + size; }

    MyVector<T>& operator=(const MyVector<T>& vector)
    {
        if (this == &vector)
        {
            return *this;
        }

        size = vector.size;
        capacity = vector.capacity;
        delete[] data;
        data = new T[capacity] {};
        for (std::size_t i {0}; i < size; i++)
        {
            data[i] = vector.data[i];
        }
        
        return *this;
    }

    MyVector<T>& operator=(MyVector<T>&& vector) noexcept
    {
        if (this == &vector)
        {
            return *this;
        }

        size = vector.size;
        capacity = vector.capacity;
        delete[] data;
        data = vector.data;

        vector.data = nullptr;
        vector.size = 0;
        vector.capacity = 0;
        
        return *this;
    }

    void reserve(int32_t _capacity)
    {
        if (_capacity > capacity)
        {
            reallocate(_capacity);
        }
    }

    void push_back(const T& elem)
    {
        if (size == capacity)
        {
            reallocate(static_cast<int32_t>(capacity) + capacity_increase);
        }
        data[size++] = elem;
    }
    
    void reallocate(int32_t _capacity)
    {
        capacity = _capacity;
        MyVector<T> t_vec {*this};

        *this = std::move(t_vec);
    }

    T pop_back()
    {
        return data[--size];
    }

    void fill(const T& value)
    {
        for (auto& elem : *this)
        {
            elem = value;
        }
    }
};

#endif