cmake_minimum_required(VERSION 3.6)
project(anri)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

#SDL2 configuration
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})

#Include local headers
include_directories(${PROJECT_SOURCE_DIR}/include)

#Set macros
add_definitions(-DANRI_DEBUG)

set(SOURCE_FILES
		include/engine/event/SDL/SDLEventHandler.h
		include/engine/event/Event.h
		include/engine/event/EventHandler.h
		include/engine/input/SDL/SDLInput.h
		include/engine/input/Input.h
        include/engine/render/SDL/SDLRenderer.h
		include/engine/render/Renderer.h
		include/engine/MemoryUsage.h
		include/engine/SimpleTimer.h
		include/game/levels/GameLevel.h
		include/game/objects/GameObject.h
		include/game/objects/GameObjectType.h
		include/game/objects/IControllable.h
		include/game/objects/IMovable.h
		include/game/objects/MovableGameObject.h
		include/game/objects/PlayerGameObject.h
		include/game/Color.h
		include/game/Game.h
        include/engine/event/EventType.h
		include/engine/Config.h
		include/engine/DebugPrint.h
		src/engine/event/SDL/SDLEventHandler.cpp
		src/engine/event/EventHandler.cpp
		src/engine/input/SDL/SDLInput.cpp
		src/engine/input/Input.cpp
		src/engine/render/SDL/SDLRenderer.cpp
		src/engine/render/Renderer.cpp
		src/engine/MemoryUsage.cpp
		src/engine/SimpleTimer.cpp
		src/engine/Config.cpp
		src/engine/DebugPrint.cpp
		src/game/levels/GameLevel.cpp
		src/game/objects/GameObject.cpp
		src/game/objects/MovableGameObject.cpp
		src/game/objects/PlayerGameObject.cpp
		src/game/Color.cpp
		src/game/Game.cpp
		src/main.cpp)

add_executable(anri ${SOURCE_FILES})
target_link_libraries(anri ${SDL2_LIBRARY})
target_link_libraries(anri ${SDL2TTF_LIBRARY})

set(TARGET_ASSETS_DIR ${TARGET_FILE_DIR}/assets)

#Copy engine_assets to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/engine_assets $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#Copy config file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/anri.conf $<TARGET_FILE_DIR:${PROJECT_NAME}>)