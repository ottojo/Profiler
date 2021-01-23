cmake_minimum_required(VERSION 3.19)
project(Profiler)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/ProfilerLib)

add_executable(testprogram main.cpp)
target_link_libraries(testprogram profilerLib)
target_include_directories(testprogram PRIVATE SYSTEM lib)
