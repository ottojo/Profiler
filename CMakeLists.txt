cmake_minimum_required(VERSION 3.17)
project(Profiler)

project(ProfilerLib)
add_library(profilerLib src/Profiler.cpp src/ScopeEvent.cpp src/ProfilerUtil.cpp src/TraceEventFile.cpp src/DurationEvent.cpp)
target_include_directories(profilerLib PUBLIC external include)
target_compile_features(profilerLib PUBLIC cxx_std_17)

option(BUILD_EXECUTABLES "build executable" OFF)
if (BUILD_EXECUTABLES)
    add_subdirectory(app)
endif ()
