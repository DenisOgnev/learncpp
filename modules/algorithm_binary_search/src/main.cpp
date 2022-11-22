#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>
#include <functional>
#include <algorithm>


template <typename T>
int32_t slow_search(const std::vector<T>& vector, T value)
{
    if (vector.size() == 0)
    {
        return -1;
    }
    
    int32_t index {0};
    for (const auto& elem : vector)
    {
        if (elem == value)
        {
            return index;
        }
        index++;
        
    }

    return -1;
}

template<typename T>
int32_t binary_search(const std::vector<T> &vector, T value)
{
    if (vector.size() == 0)
    {
        return -1;
    }
    
    int32_t low {0};
    int32_t high {static_cast<int32_t>(vector.size()) - 1};

    while (high >= low)
    {
        int32_t mid {(low + high) / 2};
        int32_t elem = vector[mid];
        if (elem == value)
        {
            return mid;
        }
        if (elem > value)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}



int main()
{
    constexpr size_t n {90000000};
    std::vector<int32_t> vector(n);

    std::iota(vector.begin(), vector.end(), 1);

    constexpr int32_t search_num {n - 2};

    // slow search
    auto start = std::chrono::high_resolution_clock::now();
    int32_t slow_result {slow_search(vector, search_num)};
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << slow_result << ", time = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "\n";

    // binary search
    start = std::chrono::high_resolution_clock::now();
    int32_t binary_result {binary_search(vector, search_num)};
    stop = std::chrono::high_resolution_clock::now();

    std::cout << binary_result << ", time = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "\n";

    // std binary search
    start = std::chrono::high_resolution_clock::now();
    int32_t std_binary_result {std::binary_search(vector.begin(), vector.end(), search_num)};
    stop = std::chrono::high_resolution_clock::now();

    std::cout << std_binary_result << ", time = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "\n";


    return 0;
};
