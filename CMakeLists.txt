set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(CrazyBattle)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

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
    "src/GameManagerDefines.h"
    "src/GameManager.h"
    "src/GameManager.cpp"
    "src/GameModeDataDefines.h"
    "src/GameModeData.h"
    "src/GameModeData.cpp"
    "src/GameLevelLoader.h"
    "src/GameLevelLoader.cpp"
    "src/GamePad.h"
    "src/GamePad.cpp"
    "src/components/PlayerComponent.h"
    "src/components/TransformComponent.h"
    "src/components/TextureComponent.h"
    "src/components/SpriteComponent.h"
    "src/components/AnimatedSpriteComponent.h"
    "src/components/PhysicsBodyComponent.h"
    "src/components/PlayerDamageComponent.h"
    "src/components/LinearAttackComponent.h"
    "src/components/AttackComponent.h"
    "src/components/ChildComponent.h"
    "src/components/TimedLifeComponent.h"
    "src/components/SineAttackComponent.h"
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
    "src/systems/PlayerEntitySpawnerSystem.h"
    "src/systems/PlayerEntitySpawnerSystem.cpp"
    "src/systems/PlayerDamageSystem.h"
    "src/systems/PlayerDamageSystem.cpp"
    "src/systems/PlayerAnimationSystem.h"
    "src/systems/PlayerAnimationSystem.cpp"
    "src/systems/PlayerAttackInputSystem.h"
    "src/systems/PlayerAttackInputSystem.cpp"
    "src/systems/LinearAttackSystem.h"
    "src/systems/LinearAttackSystem.cpp"
    "src/systems/ChildTransformSystem.h"
    "src/systems/ChildTransformSystem.cpp"
    "src/systems/TimedLifeSystem.h"
    "src/systems/TimedLifeSystem.cpp"
    "src/systems/GameModeSystem.h"
    "src/systems/GameModeSystem.cpp"
    "src/systems/GameBackgroundSystem.h"
    "src/systems/GameBackgroundSystem.cpp"
    "src/systems/UIPlayerHealthSystem.h"
    "src/systems/UIPlayerHealthSystem.cpp"
    "src/systems/SineAttackSystem.h"
    "src/systems/SineAttackSystem.cpp"
    "src/states/State.h"
    "src/states/GameState.h"
    "src/states/GameState.cpp"
    "src/states/MainMenuState.h"
    "src/states/MainMenuState.cpp"
    "src/states/GameEndState.h"
    "src/states/GameEndState.cpp"
    "src/ui/basic/UILabel.h"
    "src/ui/basic/UILabel.cpp"
    "src/ui/TitleScreenLogo.h"
    "src/ui/TitleScreenLogo.cpp"
    "src/ui/UIRendererHelper.h"
    "src/ui/UIRendererHelper.cpp"
    "src/ui/ControlsScreen.h"
    "src/ui/ControlsScreen.cpp"
    "src/ui/UIEndGameScreen.h"
    "src/ui/UIEndGameScreen.cpp"
    "src/ui/UIPregame.h"
    "src/ui/UIPregame.cpp"
    "src/ui/HealthWidget.h"
    "src/ui/HealthWidget.cpp"
)

if (MSVC)
	include_directories("libs/msvc/SDL2-2.0.8/include")
	include_directories("libs/msvc/SDL2_ttf-2.0.14/include")
	include_directories("libs/msvc/SDL2_image-2.0.3/include")
else()
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
endif()

include_directories(libs/anax/include)
add_subdirectory(libs/anax/crazy-battle_cmake)

include_directories(libs/tinyheaders)

include_directories(libs/rapidjson/include)

include_directories(libs/Box2D/Box2D)
add_subdirectory(libs/Box2D/crazy-battle_cmake)

if (MSVC)
	add_executable(CrazyBattle WIN32 ${cb_source_files})
else()
	add_executable(CrazyBattle ${cb_source_files})
endif()

target_compile_features(CrazyBattle PRIVATE cxx_range_for)

if (MSVC)
	if (CMAKE_CL_64)
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x64/SDL2_image)
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x64/SDL2_ttf)
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2-2.0.8/lib/x64/SDL2)
	else()
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x86/SDL2_image)
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf)
		target_link_libraries(CrazyBattle ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2-2.0.8/lib/x86/SDL2)
	endif()
else()
	target_link_libraries(CrazyBattle ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()

target_link_libraries(CrazyBattle ANAX)
target_link_libraries(CrazyBattle Box2D)

if (MSVC)
	file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} DEST_DIR)
	
	if (CMAKE_CL_64)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x64/SDL2_image.dll SDL2_IMAGE_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x64/libpng16-16.dll LIB_PNG_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x64/zlib1.dll LIB_ZLIB_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x64/SDL2_ttf.dll SDL2_TTF_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x64/libfreetype-6.dll LIB_FREETYPE_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2-2.0.8/lib/x64/SDL2.dll SDL2_DLL)
	else()
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x86/SDL2_image.dll SDL2_IMAGE_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x86/libpng16-16.dll LIB_PNG_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_image-2.0.3/lib/x86/zlib1.dll LIB_ZLIB_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.dll SDL2_TTF_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2_ttf-2.0.14/lib/x86/libfreetype-6.dll LIB_FREETYPE_DLL)
		file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/msvc/SDL2-2.0.8/lib/x86/SDL2.dll SDL2_DLL)
	endif()
	
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${SDL2_IMAGE_DLL} ${DEST_DIR} /yis)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${LIB_PNG_DLL} ${DEST_DIR} /yis)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${LIB_ZLIB_DLL} ${DEST_DIR} /yis)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${SDL2_TTF_DLL} ${DEST_DIR} /yis)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${LIB_FREETYPE_DLL} ${DEST_DIR} /yis)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND xcopy ${SDL2_DLL} ${DEST_DIR} /yis)
endif()
