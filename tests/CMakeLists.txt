cmake_minimum_required(VERSION 3.12)

# List all files containing tests. (Change as needed)
set(TESTFILES        # All .cpp files in tests/
    main.cpp
    vector2D_tests.cpp
    matrix2D_tests.cpp
    vector3D_tests.cpp
    matrix3D_tests.cpp
    cuboid_tests.cpp
    block_tests.cpp
    prism_tests.cpp
    drone_tests.cpp
    scene_tests.cpp
    count_tests.cpp
    plane_tests.cpp
    pyramid_tests.cpp
    triangular_tests.cpp
    circus_tests.cpp
    tent_tests.cpp
    volcano_tests.cpp
)

set(TEST_MAIN unit_tests)   # Default name for test executable (change if you wish).
set(TEST_RUNNER_PARAMS "")  # Any arguemnts to feed the test runner (change as needed).

# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------
add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} PRIVATE ${LIBRARY_NAME} doctest)
set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(${TEST_MAIN} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(${TEST_MAIN} PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME ${LIBRARY_NAME}.${TEST_MAIN}
    COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS})

# Adds a 'coverage' target.
include(CodeCoverage)

# verbose full described tests (make fulltest)
add_custom_target(fulltest
    ${TEST_MAIN} -s
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

