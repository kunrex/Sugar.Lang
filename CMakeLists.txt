cmake_minimum_required(VERSION 3.30)
project(Sugar_Lang)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(Sugar_Lang
                main.cpp)

target_link_libraries(Sugar_Lang PRIVATE Sugar)