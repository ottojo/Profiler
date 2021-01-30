add_executable(profilerExample example.main.cpp)
target_link_libraries(profilerExample profilerLib pthread)

add_executable(profilerMerge merge.main.cpp)
target_link_libraries(profilerMerge profilerLib)

# Parallel stl algorithms need TBB apparently...
find_library(TBB tbb)
if (TBB-NOTFOUND)
    message(WARNING "tbb not found")
elseif ()
    add_executable(profilerExample-transform example-transform.main.cpp)
    target_link_libraries(profilerExample-transform profilerLib tbb)
endif ()
