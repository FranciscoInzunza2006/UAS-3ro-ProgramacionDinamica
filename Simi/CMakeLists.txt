cmake_minimum_required(VERSION 4.0)
project(Simi)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(modules)

add_executable(Simi main.cpp)
target_link_libraries(Simi PUBLIC clinic)
