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

set(SOURCES src/main.cpp src/core/game.cpp src/core/game.h src/core/event_loop.cpp src/core/event_loop.h src/core/event_handler.h src/core/game_scene_renderer.cpp src/core/game_scene_renderer.h src/core/game_scene.cpp src/core/game_scene.h src/core/layer.cpp src/core/layer.h src/core/texture_manager.cpp src/core/texture_manager.h src/core/sdl_types.h src/core/sdl_types_factory.cpp src/core/sdl_types_factory.h src/core/logger.cpp src/core/logger.h src/core/game_state.cpp src/core/game_state.h src/core/game_screen_manager.cpp src/core/game_screen_manager.h src/core/game_screen.cpp src/core/game_screen.h src/core/game_states/level_game_state.cpp src/core/game_states/level_game_state.h src/core/game_scenes/level_game_scene.cpp src/core/game_scenes/level_game_scene.h src/core/game_screens/level_game_screen.cpp src/core/game_screens/level_game_screen.h src/core/gameplay/camera.cpp src/core/gameplay/camera.h src/core/gameplay/tile.cpp src/core/gameplay/tile.h src/core/gameplay/unit.cpp src/core/gameplay/unit.h src/core/drawable.h src/math/vec2.cpp src/math/vec2.h src/core/gameplay/tile_field.cpp src/core/gameplay/tile_field.h src/core/a_star/a_start.cpp src/core/a_star/a_start.h src/core/a_star/node.cpp src/core/a_star/node.h src/core/gameplay/direction.h src/core/gameplay/direction.cpp src/core/game_screens/game_over_game_screen.cpp src/core/game_screens/game_over_game_screen.h src/core/game_scenes/game_over_game_scene.cpp src/core/game_scenes/game_over_game_scene.h src/core/game_states/game_over_game_state.cpp src/core/game_states/game_over_game_state.h src/core/gameplay/boulder_spike.cpp src/core/gameplay/boulder_spike.h)

set(IMAGES
        resources/images/game_over.png
        resources/images/you_won.png
        resources/images/ground_tile.png
        resources/images/lava_tile.png
        resources/images/player_0.png
        resources/images/player_1.png
        resources/images/player_2.png
        resources/images/player_3.png
        resources/images/guard_0.png
        resources/images/guard_1.png
        resources/images/guard_2.png
        resources/images/guard_3.png
        resources/images/boulder_spike_0.png
        resources/images/boulder_spike_1.png
        resources/images/boulder_spike_2.png
        resources/images/boulder_spike_3.png
        resources/images/bed.png)

set(SCRIPTS
        resources/test_game.sh)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} ${THIRDPARTY_DEPENDENCIES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBRARIES})

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
endif ()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(
        CODE "file( GLOB SO_LIBRARIES \"${GLOBAL_OUTPUT_PATH}/3rdparty_build/lib/*.so\" )"
        CODE "file( INSTALL \${SO_LIBRARIES} DESTINATION \"${CMAKE_INSTALL_PREFIX}/lib\" )"
)
install(
        CODE "file( GLOB SO_LIBRARIES \"${GLOBAL_OUTPUT_PATH}/3rdparty_build/lib/*.so.*\" )"
        CODE "file( INSTALL \${SO_LIBRARIES} DESTINATION \"${CMAKE_INSTALL_PREFIX}/lib\" )"
)
install(FILES ${SCRIPTS} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(FILES ${IMAGES} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/test_game/images)

add_custom_target(create_zip
        COMMAND
        ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_INSTALL_PREFIX}/test_game.zip" --format=zip
        "${CMAKE_INSTALL_PREFIX}/bin"
        "${CMAKE_INSTALL_PREFIX}/lib"
        "${CMAKE_INSTALL_PREFIX}/share"
        WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX})
