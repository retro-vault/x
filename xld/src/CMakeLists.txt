project(xld)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(xld
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/bookmark.cpp  
    ${CMAKE_SOURCE_DIR}/src/bookmark.h
    ${CMAKE_SOURCE_DIR}/src/postrack.cpp  
    ${CMAKE_SOURCE_DIR}/src/postrack.h
)