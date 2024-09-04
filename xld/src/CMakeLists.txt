project(xld)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(xld
    main.cpp
    rel.cpp
)