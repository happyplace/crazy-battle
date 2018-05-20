cmake_minimum_required(VERSION 3.0)
set(ENTITYX_MAJOR_VERSION 1)
set(ENTITYX_MINOR_VERSION 1)
set(ENTITYX_PATCH_VERSION 2)
set(ENTITYX_VERSION ${ENTITYX_MAJOR_VERSION}.${ENTITYX_MINOR_VERSION}.${ENTITYX_PATCH_VERSION})

project(EntityX VERSION ${ENTITYX_VERSION})

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

# Set the source files to compile
#file(GLOB_RECURSE ENTITYX_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../entityx/*.cc)
set(ENTITYX_LIBRARY_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/../entityx/Entity.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/../entityx/Event.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/../entityx/System.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/../entityx/help/Timer.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/../entityx/help/Pool.cc"
)

# Set the include files
file(GLOB_RECURSE ENTITYX_LIBRARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../entityx/*.h)

# Add the library
add_library(EntityX STATIC ${ENTITYX_LIBRARY_INCLUDES} ${ENTITYX_LIBRARY_SOURCES})

target_compile_features(EntityX PRIVATE cxx_range_for)
