cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(crazy-battle)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

set(cb_source_files
    "src/main.cpp"
    "src/CrazyBattle.h"
    "src/CrazyBattle.cpp"
)

include_directories(framework/include)
add_subdirectory(framework)

if (MSVC)
    add_executable(crazy-battle WIN32 ${cb_source_files})
else()
    add_executable(crazy-battle ${cb_source_files})
endif()

target_link_libraries(crazy-battle PRIVATE framework)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR} CACHE PATH "Build directory" FORCE)
