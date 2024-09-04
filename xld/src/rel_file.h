#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <fstream>
#include <stdexcept>

namespace rel_parser {

// Exception class for parser errors
class parse_exception : public std::runtime_error {
public:
    explicit parse_exception(const std::string& message)
        : std::runtime_error("parse error: " + message) {}
};

// Enumeration for different line types in REL file
enum class line_type {
    header,
    symbol,
    area,
    text,
    relocation,
    paging,
    unknown
};

// Struct for header line
struct header {
    uint16_t areas;
    uint16_t symbols;
};

// Struct for symbol definition
struct symbol {
    std::string name;
    uint16_t value;
    bool is_definition;
};

// Struct for area definition
struct area {
    std::string label;
    uint16_t size;
    uint8_t flags;
};

// Struct for T line (assembled code)
struct text_line {
    uint16_t offset;
    std::vector<uint8_t> data;
};

// Struct for R line (relocation information)
struct relocation {
    uint16_t area_index;
    uint8_t mode;
    uint8_t data_index;
    uint16_t reference_index;
};

// Struct for P line (paging information)
struct paging {
    uint16_t area_index;
    uint8_t mode;
    uint8_t page_index;
    uint16_t page_reference;
};

// Main class for parsing and handling the REL file
class rel_file {
public:
    explicit rel_file(const std::string& filename);
    void parse();

    const header& get_header() const { return header_; }
    const std::vector<symbol>& get_symbols() const { return symbols_; }
    const std::vector<area>& get_areas() const { return areas_; }
    const std::vector<text_line>& get_text_lines() const { return text_lines_; }
    const std::vector<relocation>& get_relocations() const { return relocations_; }
    const std::vector<paging>& get_pagings() const { return pagings_; }
    const std::string& get_format_specifier() const { return format_specifier_; }

private:
    // Parses the first line format specifier (e.g., XL, XL2)
    void parse_format_specifier(const std::string& line);

    // Parses a line according to its type
    void parse_line(const std::string& line);
    
    // Determines the type of a line based on its first character
    line_type determine_line_type(const std::string& line) const;

    // Parsing functions for each specific line type
    void parse_header_line(const std::string& line);
    void parse_symbol_line(const std::string& line);
    void parse_area_line(const std::string& line);
    void parse_text_line(const std::string& line);
    void parse_relocation_line(const std::string& line);
    void parse_paging_line(const std::string& line);

    std::ifstream file_;                    // Input file stream
    std::string format_specifier_;          // Stores the first line format specifier
    header header_;                         // Stores header information
    std::vector<symbol> symbols_;           // Stores symbols
    std::vector<area> areas_;               // Stores areas
    std::vector<text_line> text_lines_;     // Stores text lines
    std::vector<relocation> relocations_;   // Stores relocation information
    std::vector<paging> pagings_;           // Stores paging information
};

} // namespace rel_parser
