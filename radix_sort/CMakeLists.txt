cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(playground1 play.cpp)

find_package(GTest REQUIRED)

enable_testing()

add_executable(sort_testing test.cpp)
target_link_libraries(sort_testing ${GTEST_LIBRARIES})

add_test(sort_test sort_testing)
