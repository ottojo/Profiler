add_executable(profilerExample example.main.cpp)
target_link_libraries(profilerExample profilerLib pthread)

add_executable(profilerMerge merge.main.cpp)
target_link_libraries(profilerMerge profilerLib)
