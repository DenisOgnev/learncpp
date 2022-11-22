#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>
#include <functional>
#include <algorithm>


template<typename T>
size_t find_smallest(const std::vector<T>& vector)
{
    if (vector.size() == 0)
    {
        throw std::runtime_error("Wrong size of vector");
    }
    size_t smallest_index {0};
    T smallest {vector[0]};

    for (size_t i {1}; i < vector.size(); i++)
    {
        if (vector[i] < smallest)
        {
            smallest_index = i;
            smallest = vector[smallest_index];
        }
    }
    
    return smallest_index;
}


template<typename T>
void selection_sort(std::vector<T>& vector)
{
    if (vector.size() == 0)
    {
        return;
    }
    std::vector<int32_t> result;
    
    size_t t_size {vector.size()};
    for (size_t i {0}; i < t_size; i++)
    {
        size_t smallest_index {find_smallest(vector)};
        result.push_back(vector[smallest_index]);
        vector.erase(vector.begin() + smallest_index);
    }

    vector.swap(result);
}


template<typename T>
void bubble_sort(std::vector<T>& vector)
{
    for (size_t i {0}; i < vector.size(); i++)
    {
        for (size_t j {i + 1}; j < vector.size(); j++)
        {
            if (vector[i] > vector[j])
            {
                std::swap(vector[i], vector[j]);
            }
        }
    }
}


template<typename T>
std::vector<T> quick_sort(std::vector<T>& vector)
{
    std::vector<T> result {};
    if (vector.size() < 2)
    {
        return result;
    }
    else
    {
        size_t mid {vector.size() / 2};
        T mid_elem {vector[mid]};

        std::vector<T> less {};
        for (size_t i {0}; i < vector.size(); i++)
        {
            if (i == mid) continue;
            if (vector[i] < mid_elem)
            {
                less.push_back(vector[i]);
            }
        }
        
        std::vector<T> greater {};
        for (size_t i {0}; i < vector.size(); i++)
        {
            if (i == mid) continue;
            if (vector[i] > mid_elem)
            {
                greater.push_back(vector[i]);
            }
        }

        quick_sort(less);
        quick_sort(greater);

        vector.clear();
        vector.insert(vector.end(), less.begin(), less.end());
        vector.push_back(mid_elem);
        vector.insert(vector.end(), greater.begin(), greater.end());
    }
}


int main()
{
    constexpr size_t n {50000};
    std::vector<int32_t> vector(n);
    std::iota(vector.begin(), vector.end(), 1);


    // selection sort
    std::shuffle(vector.begin(), vector.end(), std::mt19937 {std::random_device {}()});
    auto start {std::chrono::high_resolution_clock::now()};
    selection_sort(vector);
    auto stop {std::chrono::high_resolution_clock::now()};
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "ms\n";
        

    // bubble sort
    std::shuffle(vector.begin(), vector.end(), std::mt19937 {std::random_device {}()});
    start = std::chrono::high_resolution_clock::now();
    bubble_sort(vector);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "ms\n";


    // std sort
    std::shuffle(vector.begin(), vector.end(), std::mt19937 {std::random_device {}()});
    start = std::chrono::high_resolution_clock::now();
    std::sort(vector.begin(), vector.end(), std::less());
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "ms\n";


    // quick sort
    std::shuffle(vector.begin(), vector.end(), std::mt19937 {std::random_device {}()});    
    start = std::chrono::high_resolution_clock::now();
    quick_sort(vector);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "ms\n";


    return 0;
};
