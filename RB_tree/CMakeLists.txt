cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)


enable_testing()

add_executable(rb_testing test.cpp)
target_link_libraries(rb_testing ${GTEST_LIBRARIES})

add_test(rb-tree_test rb_testing)
