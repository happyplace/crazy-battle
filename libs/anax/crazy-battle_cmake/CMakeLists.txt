project (ANAX)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the source files to compile
file(GLOB_RECURSE ANAX_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)

# Set the include files
file(GLOB_RECURSE ANAX_LIBRARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp)

# Add the library
add_library(ANAX STATIC ${ANAX_LIBRARY_INCLUDES} ${ANAX_LIBRARY_SOURCES})

target_compile_features(ANAX PRIVATE cxx_range_for)
