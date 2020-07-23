set(BUILD_SHARED_LIBS OFF)
add_subdirectory(SDL)

add_library(stb INTERFACE)

target_include_directories(stb
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}/stb
)
