cmake_minimum_required(VERSION 3.1)

project (framework)

add_definitions(-DBUILDING_DLL)

include_directories(include)

set(fw_source_files
    "include/FrameworkExport.h"
    "include/Game.h"
)

set(fw_source_files
    "src/Game.cpp"
)

if (MSVC)
    include_directories("libs/msvc/SDL2/include")
else()
endif()

add_library(framework SHARED ${fw_source_files})

target_compile_features(framework PRIVATE cxx_range_for)

if (MSVC)
    if (CMAKE_CL_64)
        target_link_libraries(framework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x64/SDL2.lib)
    else()
        target_link_libraries(framework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x86/SDL2.lib)
    endif()
endif()

if (MSVC)
    if (CMAKE_CL_64)
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x64/SDL2.dll SDL2_DLL)
    else()
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x86/SDL2.dll SDL2_DLL)
    endif()

    file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/$(Configuration)" DEST_DIR)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy "${SDL2_DLL}" "${DEST_DIR}" /yis)
endif()
