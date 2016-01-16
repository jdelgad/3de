cmake_minimum_required(VERSION 3.3)
set(CMAKE_VERBOSE_MAKEFILE false)
project(3de)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(SOURCE_FILES main.cpp)

add_executable(3de ${SOURCE_FILES})

include_directories(engine)

add_subdirectory(engine)
add_subdirectory(tests)

target_link_libraries(3de ${SDL_LIBRARY})
target_link_libraries(3de engine)