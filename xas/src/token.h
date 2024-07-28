#pragma once

#include <string>

enum class token_type {
    LABEL,
    INSTRUCTION,
    DIRECTIVE,
    REGISTER,
    IMMEDIATE_VALUE,
    ADDRESS,
    OFFSET,
    PORT,
    CONDITION,
    VECTOR,
    MODE,
    BIT,
    COMMENT,
    IDENTIFIER,
    UNKNOWN,
    COLON,
    END_OF_FILE
};

class token {
public:
    token(token_type type, const std::string& value) : type(type), value(value) {}

    token_type get_type() const { return type; }
    const std::string& get_value() const { return value; }

private:
    token_type type;
    std::string value;
};