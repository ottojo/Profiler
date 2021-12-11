add_executable(profilerExample example.main.cpp)
target_link_libraries(profilerExample profilerLib pthread)

add_executable(profilerMerge merge.main.cpp)
target_link_libraries(profilerMerge profilerLib)

add_executable(profilerExample-flow example-flow.main.cpp)
target_link_libraries(profilerExample-flow profilerLib pthread)
set_property(TARGET profilerExample-flow PROPERTY CXX_STANDARD 20)

# Parallel stl algorithms need TBB apparently...
find_library(TBB tbb)
if (TBB-NOTFOUND)
    message(WARNING "tbb not found")
else ()
    add_executable(profilerExample-transform example-transform.main.cpp)
    target_link_libraries(profilerExample-transform profilerLib tbb)
endif ()
