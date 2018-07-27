cmake_minimum_required(VERSION 3.8)
project(test_game)

set(CMAKE_CXX_STANDARD 17)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

include(CMakeListsExt.txt)

include_directories(${THIRDPARTY_INCLUDE_PATHS} ${CMAKE_SOURCE_DIR}/src)
link_directories(${THIRDPARTY_LIBRARIES_PATHS})

set(SOURCES src/main.cpp src/core/game.cpp src/core/game.h src/core/event_loop.cpp src/core/event_loop.h src/core/event_handler.h src/core/game_scene_renderer.cpp src/core/game_scene_renderer.h src/core/game_scene.cpp src/core/game_scene.h src/core/layer.cpp src/core/layer.h src/core/texture_manager.cpp src/core/texture_manager.h src/core/sdl_types.h src/core/sdl_types_factory.cpp src/core/sdl_types_factory.h src/core/logger.cpp src/core/logger.h src/core/game_state.cpp src/core/game_state.h src/core/game_screen_manager.cpp src/core/game_screen_manager.h src/core/game_screen.cpp src/core/game_screen.h src/core/game_states/level_game_state.cpp src/core/game_states/level_game_state.h src/core/game_scenes/level_game_scene.cpp src/core/game_scenes/level_game_scene.h src/core/game_screens/level_game_screen.cpp src/core/game_screens/level_game_screen.h src/core/gameplay/camera.cpp src/core/gameplay/camera.h src/core/gameplay/tile.cpp src/core/gameplay/tile.h src/core/gameplay/cell_field.cpp src/core/gameplay/cell_field.h src/core/gameplay/cell.cpp src/core/gameplay/cell.h src/core/gameplay/unit.cpp src/core/gameplay/unit.h src/core/drawable.h src/math/vec2.cpp src/math/vec2.h src/core/gameplay/player.cpp src/core/gameplay/player.h src/core/gameplay/tile_field.cpp src/core/gameplay/tile_field.h src/core/a_star/a_start.cpp src/core/a_star/a_start.h src/core/a_star/node.cpp src/core/a_star/node.h)

set(IMAGES
        resources/images/ground_tile.png
        resources/images/player_0.png
        resources/images/player_1.png
        resources/images/player_2.png
        resources/images/player_3.png)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} ${THIRDPARTY_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBRARIES})

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
install(FILES ${IMAGES}
        DESTINATION ${PROJECT_BINARY_DIR}/resources/images)

add_custom_target(create_zip COMMAND
        ${CMAKE_COMMAND} -E tar "cfv" "${PROJECT_BINARY_DIR}/test_game.zip" --format=zip
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}"
        "${PROJECT_BINARY_DIR}/resources")