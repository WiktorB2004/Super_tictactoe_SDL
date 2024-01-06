# Set directory shortcuts
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(UTILS_DIR ${CMAKE_SOURCE_DIR}/utils)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Include main header files
include_directories(${INCLUDE_DIR})

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)

# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})

# Link each test suite header files
include_directories(${TEST_DIR}/engine_test/include)
include_directories(${TEST_DIR}/gameplay_test/include)
include_directories(${TEST_DIR}/bot_test/include)
include_directories(${TEST_DIR}/utils_test/include)

# Set all test suites source files
set(ENGINE_TEST_SOURCES
    ${UTILS_DIR}/engine_utils.c
    ${SOURCE_DIR}/engine/engine.c
    ${UTILS_DIR}/sdl_utils.c
    ${SOURCE_DIR}/engine/sdl_display.c
    ${TEST_DIR}/engine_test/src/sample_test.c
    ${TEST_DIR}/engine_test/engine_test.c
)

set(GAMEPLAY_TEST_SOURCES
    ${UTILS_DIR}/gameplay_utils.c
    ${SOURCE_DIR}/gameplay/gameplay.c
    ${TEST_DIR}/gameplay_test/src/sample_test.c
    ${TEST_DIR}/gameplay_test/gameplay_test.c
)

set(BOT_TEST_SOURCES
    ${UTILS_DIR}/bot_utils.c
    ${SOURCE_DIR}/game_bot/bot.c
    ${SOURCE_DIR}/game_bot/generate_move.c
    ${TEST_DIR}/bot_test/src/sample_test.c
    ${TEST_DIR}/bot_test/bot_test.c
)

set(HOST_TEST_SOURCES
    ${UTILS_DIR}/host_utils.c
    ${SOURCE_DIR}/game_host/game_hosting.c
    ${TEST_DIR}/host_test/src/sample_test.c
    ${TEST_DIR}/host_test/host_test.c
)

set(UTILS_TEST_SOURCES
    ${UTILS_DIR}/engine_utils.c
    ${UTILS_DIR}/gameplay_utils.c
    ${UTILS_DIR}/sdl_utils.c
    ${UTILS_DIR}/bot_utils.c
    ${TEST_DIR}/utils_test/src/sample_test.c
    ${TEST_DIR}/utils_test/utils_test.c
)

# Include Unity
include_directories(${LIB_DIR}/Unity)

# Add an executable for tests
add_executable(test_engine ${ENGINE_TEST_SOURCES})
add_executable(test_gameplay  ${GAMEPLAY_TEST_SOURCES})
add_executable(test_bot  ${BOT_TEST_SOURCES})
add_executable(test_host  ${HOST_TEST_SOURCES})
add_executable(test_utils ${UTILS_TEST_SOURCES})

# Link Unity library with test executable
target_link_libraries(test_engine PRIVATE unity)
target_link_libraries(test_engine PRIVATE m)

target_link_libraries(test_gameplay PRIVATE unity)
target_link_libraries(test_gameplay PRIVATE m)

target_link_libraries(test_bot PRIVATE unity)
target_link_libraries(test_bot PRIVATE m)

target_link_libraries(test_host PRIVATE unity)
target_link_libraries(test_host PRIVATE m)

target_link_libraries(test_utils PRIVATE unity)
target_link_libraries(test_utils PRIVATE m)

# Optionally, set output directories for test files
set_target_properties(test_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/engine
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/engine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/engine
)
set_target_properties(test_gameplay PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/gameplay
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/gameplay
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/gameplay
)
set_target_properties(test_bot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/bot
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/bot
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/bot
)
set_target_properties(test_host PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/bot
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/bot
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/bot
)
set_target_properties(test_utils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/utils
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/utils
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/utils
)

# Add tests
enable_testing()
add_test(NAME engine COMMAND test_engine)
add_test(NAME gameplay COMMAND test_gameplay)
add_test(NAME bot COMMAND test_bot)
add_test(NAME host COMMAND test_host)
add_test(NAME utils COMMAND test_utils)
