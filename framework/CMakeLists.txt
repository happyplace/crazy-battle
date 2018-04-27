set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project (framework)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

add_definitions(-DBUILDING_DLL)

include_directories(include)

set(fw_include_files
    "include/gf/FrameworkExport.h"
    "include/gf/Game.h"
	"include/gf/Renderer.h"
)

set(fw_source_files
    "src/Game.cpp"
	"src/Renderer.cpp"
)

include_directories(libs/entityx)
add_subdirectory(libs/entityx)

if (MSVC)
    include_directories("libs/msvc/SDL2/include")
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
endif()

add_library(framework SHARED ${fw_include_files} ${fw_source_files})

target_compile_features(framework PRIVATE cxx_range_for)

target_link_libraries(framework PRIVATE entityx)

if (MSVC)
    if (CMAKE_CL_64)
        target_link_libraries(framework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x64/SDL2.lib)
    else()
        target_link_libraries(framework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x86/SDL2.lib)
    endif()
else()
    target_link_libraries(CrazyBattle ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
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
