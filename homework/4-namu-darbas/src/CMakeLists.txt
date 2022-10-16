set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES test.cpp Table.h)

add_executable(${BINARY}_run test2.cpp Tree.h)

add_library(${BINARY}_lib STATIC test.cpp Table.h)