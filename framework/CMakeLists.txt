set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project (framework)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

add_definitions(-DBUILDING_DLL)

set(fw_include_files
    "include/gf/FrameworkExport.h"
    "include/gf/Game.h"
    "include/gf/Renderer.h"
    "include/gf/GameMode.h"
    "include/gf/components/SpriteComponent.h"
    "include/gf/systems/SpriteRendererSystem.h"
)

set(fw_source_files
    "src/Game.cpp"
    "src/Renderer.cpp"
    "src/GameMode.cpp"
    "src/systems/SpriteRendererSystem.cpp"
)

add_subdirectory(libs/entityx)

if (MSVC)
    set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS} 
        "{FRAMEWORK_ROOT}libs/msvc/SDL2/include"
        "{FRAMEWORK_ROOT}libs/msvc/SDL2_image/include"
        "{FRAMEWORK_ROOT}libs/msvc/SDL2_ttf/include"
    )
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
    )
endif()

set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS}
    "{FRAMEWORK_ROOT}include"
    "{FRAMEWORK_ROOT}libs/entityx"
)

SET_PROPERTY(GLOBAL PROPERTY GlobalFrameworkIncludes ${FRAMEWORK_INCLUDE_DIRS})
foreach(includeDir ${FRAMEWORK_INCLUDE_DIRS})
    string(REPLACE "{FRAMEWORK_ROOT}" "" full_include_dir ${includeDir})
    include_directories(${full_include_dir})
endforeach()

add_library(framework SHARED ${fw_include_files} ${fw_source_files})

target_compile_features(framework PRIVATE cxx_range_for)

target_link_libraries(framework entityx)

if (MSVC)
    if (CMAKE_CL_64)
        target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x64/SDL2.lib)
        target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image/lib/x64/SDL2_image.lib)
        target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf/lib/x64/SDL2_ttf.lib)
    else()
        target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x86/SDL2.lib)
                target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image/lib/x86/SDL2_image.lib)
        target_link_libraries(framework ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf/lib/x86/SDL2_ttf.lib)
    endif()
else()
    target_link_libraries(framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()

if (MSVC)
    if (CMAKE_CL_64)
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x64/SDL2.dll SDL2_DLL)
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image/lib/x64/SDL2_image.dll SDL2_IMAGE_DLL)
    else()
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2/lib/x86/SDL2.dll SDL2_DLL)
        file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image/lib/x86/SDL2_image.dll SDL2_IMAGE_DLL)
    endif()

    file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/$(Configuration)" DEST_DIR)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy "${SDL2_DLL}" "${DEST_DIR}" /yis)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy "${SDL2_IMAGE_DLL}" "${DEST_DIR}" /yis)
endif()
