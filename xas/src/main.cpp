// xc compiler main module
// 
// MIT License (see: LICENSE)
// copyright (C) 2021 tomaz stih
//
// tstih
#include "scanner.h"
#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    scanner scanner_instance(source);
    std::vector<token> tokens = scanner_instance.scan_tokens();

    lexer lexer_instance(tokens);
    lexer_instance.parse();

    return 0;
}
