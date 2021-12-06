cmake_minimum_required(VERSION 3.20)
project(HW)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW
        main.cpp)
target_link_libraries(HW ncurses)
#?????