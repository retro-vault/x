#include "scanner.h"

std::unordered_map<std::string, token_type> scanner::keywords = {
    {"NOP", token_type::INSTRUCTION},
    {"LD", token_type::INSTRUCTION},
    {"INC", token_type::INSTRUCTION},
    // Add more instructions, directives, registers, etc.
};

std::vector<token> scanner::scan_tokens() {
    std::vector<token> tokens;
    while (!is_at_end()) {
        skip_whitespace();
        tokens.push_back(scan_token());
    }
    tokens.emplace_back(token_type::END_OF_FILE, "");
    return tokens;
}

char scanner::advance() {
    return source[current_index++];
}

bool scanner::is_at_end() const {
    return current_index >= source.size();
}

char scanner::peek() const {
    return is_at_end() ? '\0' : source[current_index];
}

char scanner::peek_next() const {
    return (current_index + 1 >= source.size()) ? '\0' : source[current_index + 1];
}

void scanner::skip_whitespace() {
    while (!is_at_end() && std::isspace(peek())) {
        advance();
    }
}

token scanner::scan_token() {
    char c = advance();
    if (std::isalpha(c)) return identifier();
    if (std::isdigit(c)) return number();
    if (c == ';') return comment();

    return token(token_type::UNKNOWN, std::string(1, c));
}

token scanner::identifier() {
    size_t start = current_index - 1;
    while (!is_at_end() && (std::isalnum(peek()) || peek() == '_')) {
        advance();
    }
    std::string value = source.substr(start, current_index - start);
    token_type type = token_type::IDENTIFIER;
    if (keywords.find(value) != keywords.end()) {
        type = keywords[value];
    }
    return token(type, value);
}

token scanner::number() {
    size_t start = current_index - 1;
    while (!is_at_end() && std::isdigit(peek())) {
        advance();
    }
    return token(token_type::IMMEDIATE_VALUE, source.substr(start, current_index - start));
}

token scanner::comment() {
    size_t start = current_index - 1;
    while (!is_at_end() && peek() != '\n') {
        advance();
    }
    return token(token_type::COMMENT, source.substr(start, current_index - start));
}
