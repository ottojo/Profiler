project(ProfilerLib)

add_library(profilerLib Profiler.cpp ScopeEvent.cpp ProfilerUtil.cpp)
target_include_directories(profilerLib PRIVATE SYSTEM external)
