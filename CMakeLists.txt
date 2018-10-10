cmake_minimum_required(VERSION 3.6)
project(anri)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_BUILD_TYPE Debug)

#SDL2 configuration
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2MIXER REQUIRED)
find_package(SDL2IMAGE REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})
include_directories(${SDL2MIXER_INCLUDE_DIR})
include_directories(${SDL2IMAGE_INCLUDE_DIR})

#Include local headers
include_directories(${PROJECT_SOURCE_DIR}/include)

#Set macros
add_definitions(-DANRI_DEBUG)
add_definitions(-Wall)

set(SOURCE_FILES
		include/engine/math/Vec2.h
        include/engine/event/EventHandler.h
		include/engine/event/Event.h
		include/engine/event/EventType.h
        include/engine/input/Input.h
        include/engine/render/Renderer.h
		include/engine/sound/SoundSystem.h
		include/engine/graphics/RGBColor.h
		include/engine/graphics/Texture.h
		include/engine/graphics/Particle.h
		include/engine/graphics/ParticleSystem.h
		include/engine/messaging/Message.h
		include/engine/messaging/MessageSystem.h
		include/engine/MemoryUsage.h
		include/engine/SimpleTimer.h
		include/engine/Config.h
		include/engine/Random.h
		include/engine/DebugPrint.h
		include/engine/DebugInfo.h
		include/engine/System.h
		include/engine/Allocator.h
		include/game/levels/GameLevel.h
		include/game/objects/GameObject.h
		include/game/objects/GameObjectType.h
		include/game/objects/MovableGameObject.h
		include/game/objects/PlayerGameObject.h
		include/game/objects/ui/UiGameObject.h
		include/game/components/Component.h
		include/game/components/GraphicsComponent.h
		include/game/Game.h
        src/engine/event/EventHandler.cpp
        src/engine/input/Input.cpp
		src/engine/render/Renderer.cpp
		src/engine/sound/SoundSystem.cpp
		src/engine/graphics/Texture.cpp
		src/engine/graphics/ParticleSystem.cpp
		src/engine/messaging/Message.cpp
		src/engine/messaging/MessageSystem.cpp
		src/engine/MemoryUsage.cpp
		src/engine/SimpleTimer.cpp
		src/engine/Config.cpp
		src/engine/Random.cpp
		src/engine/DebugPrint.cpp
		src/engine/System.cpp
		src/engine/Allocator.cpp
		src/game/levels/GameLevel.cpp
		src/game/objects/GameObject.cpp
		src/game/objects/MovableGameObject.cpp
		src/game/objects/PlayerGameObject.cpp
		src/game/objects/ui/UiGameObject.cpp
		src/game/components/GraphicsComponent.cpp
		src/game/Game.cpp
		src/main.cpp)

add_executable(anri ${SOURCE_FILES})
target_link_libraries(anri ${SDL2_LIBRARY})
target_link_libraries(anri ${SDL2TTF_LIBRARY})
target_link_libraries(anri ${SDL2MIXER_LIBRARY})
target_link_libraries(anri ${SDL2IMAGE_LIBRARY})
if (WIN32)
	target_link_libraries(anri psapi)
endif (WIN32)

set(TARGET_ASSETS_DIR ${TARGET_FILE_DIR}/assets)

#Copy engine_assets to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/engine_assets $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#Copy config file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/anri.conf $<TARGET_FILE_DIR:${PROJECT_NAME}>/anri.conf)