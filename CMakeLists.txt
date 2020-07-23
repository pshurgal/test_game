cmake_minimum_required(VERSION 3.8)
project(test_game)

add_subdirectory(thirdparty)

add_executable(${PROJECT_NAME} "")

if(WIN32)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

set(SRC_ROOT "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES
        ${SRC_ROOT}/algorithm/a_start.cpp
        ${SRC_ROOT}/algorithm/a_start.h

        ${SRC_ROOT}/container/sparse_map.h

        ${SRC_ROOT}/ecs/components_view.h
        ${SRC_ROOT}/ecs/entity.cpp
        ${SRC_ROOT}/ecs/entity.h
        ${SRC_ROOT}/ecs/pool.h
        ${SRC_ROOT}/ecs/registry.h

        ${SRC_ROOT}/events/event.h
        ${SRC_ROOT}/events/event_handler.h
        ${SRC_ROOT}/events/event_pump.cpp
        ${SRC_ROOT}/events/event_pump.h

        ${SRC_ROOT}/game/field/tile.cpp
        ${SRC_ROOT}/game/field/tile.h
        ${SRC_ROOT}/game/field/tile_field.cpp
        ${SRC_ROOT}/game/field/tile_field.h
        ${SRC_ROOT}/game/states/game_over.cpp
        ${SRC_ROOT}/game/states/game_over.h
        ${SRC_ROOT}/game/states/level.cpp
        ${SRC_ROOT}/game/states/level.h
        ${SRC_ROOT}/game/systems/damage_system.cpp
        ${SRC_ROOT}/game/systems/damage_system.h
        ${SRC_ROOT}/game/systems/despawn_system.cpp
        ${SRC_ROOT}/game/systems/despawn_system.h
        ${SRC_ROOT}/game/systems/movement_system.cpp
        ${SRC_ROOT}/game/systems/movement_system.h
        ${SRC_ROOT}/game/systems/path_system.cpp
        ${SRC_ROOT}/game/systems/path_system.h
        ${SRC_ROOT}/game/systems/patrol_system.cpp
        ${SRC_ROOT}/game/systems/patrol_system.h
        ${SRC_ROOT}/game/systems/visual_system.cpp
        ${SRC_ROOT}/game/systems/visual_system.h
        ${SRC_ROOT}/game/game.cpp
        ${SRC_ROOT}/game/game.h
        ${SRC_ROOT}/game/game_state.cpp
        ${SRC_ROOT}/game/game_state.h
        ${SRC_ROOT}/game/game_state_machine.cpp
        ${SRC_ROOT}/game/game_state_machine.h

        ${SRC_ROOT}/graphics/bitmap.cpp
        ${SRC_ROOT}/graphics/bitmap.h
        ${SRC_ROOT}/graphics/bitmap_loader.cpp
        ${SRC_ROOT}/graphics/bitmap_loader.h

        ${SRC_ROOT}/input/keyboard_key.h
        ${SRC_ROOT}/input/mouse_button.h

        ${SRC_ROOT}/launcher/main.cpp
        ${SRC_ROOT}/launcher/main.h
        $<$<BOOL:${UNIX}>:${SRC_ROOT}/launcher/main_linux.cpp>
        $<$<BOOL:${WIN32}>:${SRC_ROOT}/launcher/main_win32.cpp>

        ${SRC_ROOT}/math/rect.h
        ${SRC_ROOT}/math/vec2.h

        ${SRC_ROOT}/rendering/camera.cpp
        ${SRC_ROOT}/rendering/camera.h
        ${SRC_ROOT}/rendering/canvas.cpp
        ${SRC_ROOT}/rendering/canvas.h
        ${SRC_ROOT}/rendering/rendering_backend.cpp
        ${SRC_ROOT}/rendering/rendering_backend.h
        ${SRC_ROOT}/rendering/texture.cpp
        ${SRC_ROOT}/rendering/texture.h

        ${SRC_ROOT}/resources/texture_manager.cpp
        ${SRC_ROOT}/resources/texture_manager.h

        ${SRC_ROOT}/utils/generic_handle.h
        ${SRC_ROOT}/utils/raii_guard.h
)

set(IMAGES
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/game_over.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/you_won.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/ground_tile.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/lava_tile.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/player_0.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/player_1.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/player_2.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/player_3.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/guard_0.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/guard_1.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/guard_2.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/guard_3.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/spiked_ball_0.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/spiked_ball_1.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/spiked_ball_2.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/spiked_ball_3.png
        ${CMAKE_CURRENT_LIST_DIR}/resources/images/bed.png
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES}
        ${IMAGES}
 )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL2-static
        stb
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_target(copy_images
    COMMENT "Copyint images into build directory"
    VERBATIM
    COMMAND_EXPAND_LISTS
    COMMAND ${CMAKE_COMMAND} -E
        make_directory "${CMAKE_BINARY_DIR}/bin/images"
    COMMAND ${CMAKE_COMMAND} -E
        copy_if_different ${IMAGES} "${CMAKE_BINARY_DIR}/bin/images"
)

add_dependencies(${PROJECT_NAME} copy_images)

add_custom_target(create_zip
        COMMENT "Creating ZIP erchive of build artifacts"
        VERBATIM
        COMMAND ${CMAKE_COMMAND} -E tar "cfv"
            "${CMAKE_BINARY_DIR}/test_game-${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}.zip" --format=zip .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
