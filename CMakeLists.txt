set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(CrazyBattle)

include_directories("src")

set(cb_source_files
	"src/main.cpp"
	"src/CrazyBattle.h"
	"src/CrazyBattle.cpp"
	"src/AssetLoaderDefines.h"
	"src/AssetLoaderHelper.h"
	"src/AssetLoaderHelper.cpp"
	"src/InputManager.h"
	"src/InputManager.cpp"
	"src/GameTimer.h"
	"src/GameTimer.cpp"
	"src/components/PlayerComponent.h"
	"src/components/TransformComponent.h"
	"src/components/TextureComponent.h"
	"src/components/SpriteComponent.h"
	"src/components/AnimatedSpriteComponent.h"
	"src/components/PhysicsBodyComponent.h"
	"src/systems/PlayerMovementSystem.h"
	"src/systems/PlayerMovementSystem.cpp"
	"src/systems/SpriteRendererSystem.h"
	"src/systems/SpriteRendererSystem.cpp"
	"src/systems/AnimateSpriteUpdateSystem.h"
	"src/systems/AnimateSpriteUpdateSystem.cpp"
	"src/systems/AnimateSpriteRendererSystem.h"
	"src/systems/AnimateSpriteRendererSystem.cpp"
	"src/systems/SpriteRendererHelper.h"
	"src/systems/SpriteRendererHelper.cpp"
	"src/systems/PhysicsWorldSystem.h"
	"src/systems/PhysicsWorldSystem.cpp"
	"src/states/State.h"
	"src/states/GameState.h"
	"src/states/GameState.cpp"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

include_directories(libs/anax/include)
add_subdirectory(libs/anax/crazy-battle_cmake)

include_directories(libs/tinyheaders)

include_directories(libs/rapidjson/include)

include_directories(libs/Box2D/Box2D)
add_subdirectory(libs/Box2D/crazy-battle_cmake)

add_executable(CrazyBattle ${cb_source_files})

target_compile_features(CrazyBattle PRIVATE cxx_range_for)

target_link_libraries(CrazyBattle ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(CrazyBattle ANAX)
target_link_libraries(CrazyBattle Box2D)
