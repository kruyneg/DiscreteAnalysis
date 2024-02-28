cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(playground2 play.cpp)

enable_testing()

add_executable(avl_testing test.cpp)
target_link_libraries(avl_testing ${GTEST_LIBRARIES})

add_test(avl-tree_test avl_testing)
