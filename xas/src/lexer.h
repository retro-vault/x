#pragma once

#include "token.h"
#include <vector>
#include <iostream>

class lexer {
public:
    lexer(const std::vector<token>& tokens) : tokens(tokens), current_index(0) {}

    void parse();

private:
    std::vector<token> tokens;
    size_t current_index;

    token advance();
    bool is_at_end() const;
    token peek() const;
    token previous() const;

    void statement();
    void label();
    void instruction();
    void directive();
};
