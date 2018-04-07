set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(CrazyBattle)

include_directories("src")

set(cb_source_files
	"src/main.cpp"
	"src/CrazyBattle.h"
	"src/CrazyBattle.cpp"
	"src/components/PlayerComponent.h"
	"src/systems/PlayerMovementSystem.h"
	"src/systems/PlayerMovementSystem.cpp"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

include_directories(libs/anax/include)
add_subdirectory(libs/anax/crazy-battle_cmake)

add_executable(CrazyBattle ${cb_source_files})

target_compile_features(CrazyBattle PRIVATE cxx_range_for)

target_link_libraries(CrazyBattle ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(CrazyBattle ANAX)
