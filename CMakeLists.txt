cmake_minimum_required(VERSION 3.10)

project(AdventOfCode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCE_FILES "Day*.cc") # must do `cmake` command again to get new files

foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(FILENAME ${SOURCE_FILE} NAME_WE)
    
    add_executable(${FILENAME} ${SOURCE_FILE})
endforeach()