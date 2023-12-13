cmake_minimum_required(VERSION 3.20)
project(Menu_Assignment)

set(CMAKE_CXX_STANDARD 14)

add_executable(Menu_Assignment tests.cpp menu.cpp menu.h menu_element.cpp menu_element.h)
