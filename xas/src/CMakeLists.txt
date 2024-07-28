project(xc)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(xc 
    main.cpp
    lexer.cpp
    scanner.cpp
    token.h
    scanner.h
    lexer.h
)