#pragma once
#include <vector>

template<typename T>
void __count_sort(std::vector<T>& arr, unsigned short digit) {
    std::vector<unsigned int> counter(16, 0);
    unsigned long long int mask = (0xFULL) << 4 * digit;
    for (auto& elem : arr) {
        ++counter[(elem & mask) >> 4 * digit];
    }
    for (size_t i = 1; i < counter.size(); ++i) {
        counter[i] += counter[i - 1];
    }
    std::vector<T> result(arr.size());
    for (int i = arr.size() - 1; i >= 0; --i) {
        result[counter[(arr[i] & mask) >> 4 * digit] - 1] = arr[i];
        --counter[(arr[i] & mask) >> 4 * digit];
    }
    arr = result;
}

template<typename T>
void radix_sort(std::vector<T>& arr) {
    if (std::is_signed_v<T>) {
        for (T& elem : arr) {
            elem ^= static_cast<T>(1) << (sizeof(T) * 8 - 1);
        }
    }
    for (unsigned short i = 0; i < sizeof(T) * 2; ++i) {
        __count_sort<T>(arr, i);
    }
    if (std::is_signed_v<T>) {
        for (T& elem : arr) {
            elem ^= static_cast<T>(1) << (sizeof(T) * 8 - 1);
        }
    }
}