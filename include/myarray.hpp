#ifndef MYARRAY_HPP
#define MYARRAY_HPP

#include <cstddef>
#include <initializer_list>

template<typename T, std::size_t size>
class MyArray
{
private:
    T data[size];

public:
    MyArray<T, size>() = default;
    MyArray<T, size>(std::initializer_list<T> list) : MyArray<T, size>()
    {
        std::size_t i {0};
        for (const auto &elem : list)
        {
            data[i] = elem;
            ++i;
        }
    };
    MyArray<T, size>(const MyArray<T, size>&) = default;
    MyArray<T, size>(MyArray<T, size>&& array)
    {
        for (std::size_t i {0}; i < size; i++)
        {
            data[i] = array.data[i];
            array.data[i] = 0;
        }
    };

    std::size_t get_size() { return size; };
    T* get_data() { return data; };
    T* begin() { return data; };
    T* end() { return data + size; };
    T& operator[](int32_t index) { return data[index]; };
    MyArray<T, size>& operator=(const MyArray<T, size>&) = default;
    MyArray<T, size>& operator=(MyArray<T, size>&& array)
    {
        for (std::size_t i {0}; i < size; i++)
        {
            data[i] = array.data[i];
            array.data[i] = 0;
        }
    };    

    void fill(T value)
    {
        for (auto& elem : *this)
        {
            elem = value;
        }
    };
};

#endif