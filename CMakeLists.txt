
cmake_minimum_required(VERSION 3.17)
project(mephi_3_lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(mephi_3_lab2
        main.cpp)


project(mephi_3_lab2_test)
add_executable(mephi_3_lab2_test
        tests.cpp)
target_link_libraries(mephi_3_lab2_test gtest gtest_main )

project(mephi_3_lab2_menu)
add_executable(mephi_3_lab2_menu
        menu.cpp)
