# Set directory shortcuts
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(UTILS_DIR ${CMAKE_SOURCE_DIR}/utils)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

# Include main header files
include_directories(${INCLUDE_DIR})
include_directories(${LIB_DIR}/Unity)

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)

# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})

# Link each test suite header files
# include_directories(${TEST_DIR}/TEST_FOLDER/include)

# Set all test suites source files
set(EXAMPLE_TEST_SOURCES
    ${TEST_DIR}/game_test.c
    # ...
)

# Add an executable for tests
add_executable(example_test ${EXAMPLE_TEST_SOURCES})
# ...

# Link Unity library with test executable
target_link_libraries(example_test PRIVATE unity)
# ...

# Optionally, set output directories for test files
set_target_properties(example_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
)
# ...

# Add tests
enable_testing()
add_test(NAME example_test COMMAND example_test)