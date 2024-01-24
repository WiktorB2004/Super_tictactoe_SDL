cmake_minimum_required(VERSION 3.27)
project(Super_Tictactoe)

# SDL configuration
find_package(SDL2 REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# Add compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(OBJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/obj)

# Source files
set(SOURCES
    ${UTILS_DIR}/bot_utils.c
    ${UTILS_DIR}/engine_utils.c
    ${UTILS_DIR}/gameplay_utils.c
    ${UTILS_DIR}/host_utils.c
    ${SOURCE_DIR}/engine/engine.c
    ${SOURCE_DIR}/engine/sdl_display.c
    ${SOURCE_DIR}/game_bot/bot.c
    ${SOURCE_DIR}/game_bot/generate_move.c
    ${SOURCE_DIR}/gameplay/gameplay.c
    ${SOURCE_DIR}/game_host/game_hosting.c
    ${SOURCE_DIR}/main.c
)

# Header files
include_directories(${INCLUDE_DIR})

# Executable
add_executable(supertictactoe ${SOURCES})

# Set output directories
set_target_properties(supertictactoe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OBJ_DIR}
)

# Testing
if (NOT DEFINED RELEASE_BUILD) 
    enable_testing()
    add_subdirectory(${TEST_DIR})
endif()

# Link math.h
target_link_libraries(supertictactoe PRIVATE m)
# Link pthreads.h
target_link_libraries(supertictactoe PUBLIC pthread)
# Link SDL2
target_link_libraries(supertictactoe PUBLIC ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

