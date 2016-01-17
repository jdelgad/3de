project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(HEADER_FILES
        sector.h
        vector3D.h
        vertex.h
        world.h
        player.h)

set(SOURCE_FILES
        sector.cpp
        vertex.cpp
        world.cpp
        player.cpp)

add_library(engine STATIC ${SOURCE_FILES} ${HEADER_FILES})
