cmake_minimum_required(VERSION 3.28)

project(ProfilerLib)

add_library(profilerLib STATIC)
target_compile_features(profilerLib PUBLIC cxx_std_20)
target_compile_options(profilerLib PRIVATE -Wall -Wextra -Wpedantic)
target_sources(profilerLib
        PRIVATE
        modules/profiler_impl.cpp
        modules/ScopeEvent.cpp
        modules/DurationEvent.cpp
        PUBLIC
        FILE_SET modules
        TYPE CXX_MODULES
        FILES
        modules/profiler.cppm
        modules/Scope.cppm
        modules/TraceEvent.cppm
        modules/TraceEventFile.cppm
        modules/ProfilerUtil.cppm
)

find_package(Boost REQUIRED COMPONENTS json)
target_link_libraries(profilerLib PRIVATE Boost::json)

option(BUILD_EXECUTABLES "build executable" OFF)
if (BUILD_EXECUTABLES)
    add_subdirectory(app)
endif ()
