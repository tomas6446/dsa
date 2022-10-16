cmake_minimum_required(VERSION 3.20)
project(1-namu-darbas2)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(googletest)

