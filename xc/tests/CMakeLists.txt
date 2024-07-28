project(xc)

# Include files.
include_directories(${GTEST_PATH}/include)

# Test executable.
add_executable(tests main.cpp test-scanner.cpp)

# Link in google tests.
target_link_libraries(tests 
    gtest 
    gtest_main)

# Make sure the test data is copied.
file(COPY
    data
    DESTINATION ${EXECUTABLE_OUTPUT_PATH}
)