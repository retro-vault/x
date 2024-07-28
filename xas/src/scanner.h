#pragma once

#include "token.h"

#include <vector>
#include <cctype>
#include <unordered_map>

class scanner {
public:
    scanner(const std::string& source) : source(source), current_index(0) {}

    std::vector<token> scan_tokens();

private:
    std::string source;
    size_t current_index;

    char advance();
    bool is_at_end() const;
    char peek() const;
    char peek_next() const;
    void skip_whitespace();
    token scan_token();
    token identifier();
    token number();
    token comment();

    static std::unordered_map<std::string, token_type> keywords;
};
