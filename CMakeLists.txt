cmake_minimum_required(VERSION 3.8)
project(test_game)

set(CMAKE_CXX_STANDARD 17)

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include(CMakeListsExt.txt)

include_directories(${THIRDPARTY_INCLUDE_PATHS})
link_directories(${THIRDPARTY_LIBRARIES_PATHS})

set(SOURCES
    "main.cpp"
    "core/application.cpp"
    "core/application.h")
add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} ${THIRDPARTY_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBRARIES})
