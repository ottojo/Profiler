add_executable(profilerExample example.main.cpp)
target_link_libraries(profilerExample profilerLib pthread)

add_executable(profilerMerge merge.main.cpp)

add_executable(profilerExample-flow example-flow.main.cpp)
target_link_libraries(profilerExample-flow profilerLib pthread)
target_compile_features(profilerExample-flow PUBLIC cxx_std_20)

# Parallel stl algorithms need TBB apparently...
find_library(TBB tbb)
if (TBB-NOTFOUND)
    message(WARNING "tbb not found")
else ()
    add_executable(profilerExample-transform example-transform.main.cpp)
    target_link_libraries(profilerExample-transform profilerLib tbb)
endif ()
