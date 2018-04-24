cmake_minimum_required(VERSION 3.1)

project(crazy-battle)

set(cb_source_files
    "src/main.cpp"
)

include_directories(framework/include)
add_subdirectory(framework)

add_executable(crazy-battle WIN32 ${cb_source_files})

target_link_libraries(crazy-battle framework)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR} CACHE PATH "Build directory" FORCE)
