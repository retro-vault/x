project(xc)

# Include files.
include_directories(${GTEST_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Test executable.
add_executable(tests 
    main.cpp 
    test-scanner.cpp
    ${CMAKE_SOURCE_DIR}/src/lexer.cpp 
    ${CMAKE_SOURCE_DIR}/src/scanner.cpp 
)

# Link in google tests.
target_link_libraries(tests 
    gtest 
    gtest_main)

# Make sure the test data is copied.
file(COPY
    data
    DESTINATION ${EXECUTABLE_OUTPUT_PATH}
)