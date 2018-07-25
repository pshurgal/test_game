cmake_minimum_required(VERSION 3.8)
project(test_game)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include(CMakeListsExt.txt)

include_directories(${THIRDPARTY_INCLUDE_PATHS})
link_directories(${THIRDPARTY_LIBRARIES_PATHS})

add_executable(${PROJECT_NAME} "main.cpp")
add_dependencies(${PROJECT_NAME} ${THIRDPARTY_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBRARIES})
