#include <gtest/gtest.h>
#include <algorithm>
#include "radix_sort.hpp"

TEST(sort, simple) {
    std::vector<unsigned int> arr = {3, 2, 4, 5, 6, 1};
    radix_sort(arr);
    ASSERT_TRUE(arr == std::vector<unsigned int>({1, 2, 3, 4, 5, 6}));
}

TEST(sort, big_numbers) {
    std::vector<unsigned int> arr = {209, 1993, 8, 0, 124, 101, 36, 1000000000, 9000};
    std::vector<unsigned int> cmp = arr;
    std::sort(cmp.begin(), cmp.end());
    radix_sort(arr);
    ASSERT_TRUE(arr == cmp);
}

TEST(sort, signed_simple) {
    std::vector<int> arr = {3, -2, 4, -5, 6, 1};
    radix_sort(arr);
    ASSERT_TRUE(arr == std::vector<int>({-5, -2, 1, 3, 4, 6}));
}

TEST(sort, signed_big_numbers) {
    std::vector<long long> arr = {209, __LONG_LONG_MAX__, 8, 0, 124, 101, 36, -1000000000, 9000, -__LONG_LONG_MAX__};
    std::vector<long long> cmp = arr;
    std::sort(cmp.begin(), cmp.end());
    radix_sort(arr);
    ASSERT_TRUE(arr == cmp);
}

TEST(sort, signed_eq_numbers) {
    std::vector<int> arr = {0, -1, 0, 1, 0, 111, -100, -100, 111, -1};
    std::vector<int> cmp = arr;
    std::sort(cmp.begin(), cmp.end());
    radix_sort(arr);
    ASSERT_TRUE(arr == cmp);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}