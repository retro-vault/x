#include "lexer.h"

void lexer::parse() {
    while (!is_at_end()) {
        statement();
    }
}

token lexer::advance() {
    if (!is_at_end()) current_index++;
    return previous();
}

bool lexer::is_at_end() const {
    return current_index >= tokens.size() || tokens[current_index].get_type() == token_type::END_OF_FILE;
}

token lexer::peek() const {
    return tokens[current_index];
}

token lexer::previous() const {
    return tokens[current_index - 1];
}

void lexer::statement() {
    if (peek().get_type() == token_type::LABEL) {
        label();
    } else if (peek().get_type() == token_type::INSTRUCTION) {
        instruction();
    } else if (peek().get_type() == token_type::DIRECTIVE) {
        directive();
    } else {
        advance(); // Skip unknown tokens or handle errors
    }
}

void lexer::label() {
    // Handle label logic
    advance(); // Consume the label token
    if (peek().get_type() == token_type::COLON) {
        advance(); // Consume the colon
    }
}

void lexer::instruction() {
    // Handle instruction logic
    advance(); // Consume the instruction token
    while (!is_at_end() && peek().get_type() != token_type::COMMENT) {
        advance(); // Consume operands
    }
}

void lexer::directive() {
    // Handle directive logic
    advance(); // Consume the directive token
    while (!is_at_end() && peek().get_type() != token_type::COMMENT) {
        advance(); // Consume operands
    }
}
