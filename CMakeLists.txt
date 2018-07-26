cmake_minimum_required(VERSION 3.8)
project(test_game)

set(CMAKE_CXX_STANDARD 17)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include(CMakeListsExt.txt)

include_directories(${THIRDPARTY_INCLUDE_PATHS} ${CMAKE_SOURCE_DIR})
link_directories(${THIRDPARTY_LIBRARIES_PATHS})

set(SOURCES
        main.cpp
        core/game.cpp
        core/game.h
        core/event_loop.cpp
        core/event_loop.h
        core/event_handler.h
        core/game_scene_renderer.cpp
        core/game_scene_renderer.h
        core/game_scene.cpp
        core/game_scene.h
        core/layer.cpp
        core/layer.h
        core/texture_manager.cpp
        core/texture_manager.h
        core/sdl_types.h
        core/sdl_types_factory.cpp
        core/sdl_types_factory.h
        core/logger.cpp
        core/logger.h
        core/game_state.cpp
        core/game_state.h
        core/game_screen_manager.cpp
        core/game_screen_manager.h
        core/game_scenes/sample_game_scene.cpp
        core/game_scenes/sample_game_scene.h
        core/game_screens/sample_game_screen.cpp
        core/game_screens/sample_game_screen.h
        core/game_screen.cpp
        core/game_screen.h
        core/game_states/sample_game_state.cpp
        core/game_states/sample_game_state.h)

set(IMAGES
        resources/images/template.png)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} ${THIRDPARTY_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBRARIES})

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
install(FILES ${IMAGES}
        DESTINATION ${PROJECT_BINARY_DIR}/resources/images)
