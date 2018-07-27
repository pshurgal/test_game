cmake_minimum_required(VERSION 3.8)
project(test_game)

set(CMAKE_CXX_STANDARD 17)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include(CMakeListsExt.txt)

include_directories(${THIRDPARTY_INCLUDE_PATHS} ${CMAKE_SOURCE_DIR})
link_directories(${THIRDPARTY_LIBRARIES_PATHS})

set(SOURCES main.cpp core/game.cpp core/game.h core/event_loop.cpp core/event_loop.h core/event_handler.h core/game_scene_renderer.cpp core/game_scene_renderer.h core/game_scene.cpp core/game_scene.h core/layer.cpp core/layer.h core/texture_manager.cpp core/texture_manager.h core/sdl_types.h core/sdl_types_factory.cpp core/sdl_types_factory.h core/logger.cpp core/logger.h core/game_state.cpp core/game_state.h core/game_screen_manager.cpp core/game_screen_manager.h core/game_screen.cpp core/game_screen.h core/game_states/level_game_state.cpp core/game_states/level_game_state.h core/game_scenes/level_game_scene.cpp core/game_scenes/level_game_scene.h core/game_screens/level_game_screen.cpp core/game_screens/level_game_screen.h core/gameplay/camera.cpp core/gameplay/camera.h core/gameplay/tile.cpp core/gameplay/tile.h core/gameplay/cell_field.cpp core/gameplay/cell_field.h core/gameplay/cell.cpp core/gameplay/cell.h core/gameplay/unit.cpp core/gameplay/unit.h core/drawable.h math/vec2.cpp math/vec2.h core/gameplay/player.cpp core/gameplay/player.h core/gameplay/tile_field.cpp core/gameplay/tile_field.h core/gameplay/a_start.cpp core/gameplay/a_start.h)

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