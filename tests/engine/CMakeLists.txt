include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES
        vector3D_test.cpp
        vertex_test.cpp
        world_test.cpp
        sector_test.cpp)

add_executable(runUnitTests ${SOURCE_FILES})

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests engine)
