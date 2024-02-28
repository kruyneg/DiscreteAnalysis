#include <gtest/gtest.h>
#include <sstream>
#include "bin_tree.hpp"
#include "avl_tree.hpp"

TEST(bin_tree, insert) {
    bin_tree<int> t;
    t.insert(2);
    t.insert(1);
    t.insert(3);
    ASSERT_TRUE(t.contains(1));
    ASSERT_TRUE(t.contains(2));
    ASSERT_TRUE(t.contains(3));
}

TEST(bin_tree, initializer_list_constructor) {
    bin_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    ASSERT_TRUE(tree.size() == 15);
    {
        ASSERT_TRUE(tree.contains(3));
        ASSERT_TRUE(tree.contains(7));
        ASSERT_TRUE(tree.contains(14));
        ASSERT_TRUE(tree.contains(15));
        ASSERT_TRUE(tree.contains(18));
        ASSERT_TRUE(tree.contains(21));
        ASSERT_TRUE(tree.contains(25));
        ASSERT_TRUE(tree.contains(45));
        ASSERT_TRUE(tree.contains(50));
        ASSERT_TRUE(tree.contains(51));
        ASSERT_TRUE(tree.contains(61));
        ASSERT_TRUE(tree.contains(80));
        ASSERT_TRUE(tree.contains(82));
        ASSERT_TRUE(tree.contains(88));
        ASSERT_TRUE(tree.contains(100));
    }
    ASSERT_FALSE(tree.contains(0));
    ASSERT_FALSE(tree.contains(99));
}

TEST(bin_tree, iterator) {
    bin_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    std::stringstream ss;
    for (int& elem : tree) {
        ss << elem << ' ';
    }
    ASSERT_EQ(ss.str(), "3 7 14 15 18 21 25 45 50 51 61 80 82 88 100 ");
}

TEST(bin_tree, erase) {
    bin_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    tree.erase(14);
    tree.erase(82);
    tree.erase(50);
    tree.erase(45);
    tree.erase(99);

    std::stringstream ss;
    for (int& elem : tree) {
        ss << elem << ' ';
    }
    ASSERT_EQ(ss.str(), "3 7 15 18 21 25 51 61 80 88 100 ");
}

TEST(bin_tree, find) {
    bin_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    std::stringstream ss;
    for (auto itr1 = tree.find(21), itr2 = tree.find(80);itr1 != itr2; ++itr1) {
        ss << *itr1 << ' ';
    }
    ASSERT_TRUE(ss.str() == "21 25 45 50 51 61 ");
    ASSERT_EQ(tree.find(99), tree.end());
}

TEST(avl_tree, insert) {
    avl_tree<int> t;
    t.insert(2);
    t.insert(1);
    t.insert(3);
    ASSERT_TRUE(t.contains(1));
    ASSERT_TRUE(t.contains(2));
    ASSERT_TRUE(t.contains(3));
}

TEST(avl_tree, initializer_list_constructor) {
    avl_tree<int> tree{3, 7, 14, 15, 18, 21, 25, 45, 50, 51, 61, 80, 82, 88, 100};
    ASSERT_TRUE(tree.size() == 15);
    {
        ASSERT_TRUE(tree.contains(3));
        ASSERT_TRUE(tree.contains(7));
        ASSERT_TRUE(tree.contains(14));
        ASSERT_TRUE(tree.contains(15));
        ASSERT_TRUE(tree.contains(18));
        ASSERT_TRUE(tree.contains(21));
        ASSERT_TRUE(tree.contains(25));
        ASSERT_TRUE(tree.contains(45));
        ASSERT_TRUE(tree.contains(50));
        ASSERT_TRUE(tree.contains(51));
        ASSERT_TRUE(tree.contains(61));
        ASSERT_TRUE(tree.contains(80));
        ASSERT_TRUE(tree.contains(82));
        ASSERT_TRUE(tree.contains(88));
        ASSERT_TRUE(tree.contains(100));
    }
    ASSERT_FALSE(tree.contains(0));
    ASSERT_FALSE(tree.contains(99));
}

TEST(avl_tree, iterator) {
    avl_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    std::stringstream ss;
    for (int& elem : tree) {
        ss << elem << ' ';
    }
    ASSERT_EQ(ss.str(), "3 7 14 15 18 21 25 45 50 51 61 80 82 88 100 ");
}

TEST(avl_tree, erase) {
    avl_tree<int> tree{100, 88, 82, 80, 61, 51, 50, 45, 25, 21, 18, 15, 14, 7, 3};
    tree.erase(14);
    tree.erase(7);
    tree.erase(51);
    tree.erase(45);
    tree.erase(99);

    std::stringstream ss;
    for (int& elem : tree) {
        ss << elem << ' ';
    }
    ASSERT_EQ(ss.str(), "3 15 18 21 25 50 61 80 82 88 100 ");
}

TEST(avl_tree, find) {
    avl_tree<int> tree{25, 14, 61, 3, 18, 50, 88, 7, 15, 21, 45, 51, 80, 100, 82};
    std::stringstream ss;
    for (auto itr1 = tree.find(21), itr2 = tree.find(80);itr1 != itr2; ++itr1) {
        ss << *itr1 << ' ';
    }
    ASSERT_TRUE(ss.str() == "21 25 45 50 51 61 ");
    ASSERT_EQ(tree.find(99), tree.end());
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}