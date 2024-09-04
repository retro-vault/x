#include "rel_file.h"
#include <sstream>
#include <iostream>

namespace rel_parser {

// Function to parse the format specifier line
void rel_file::parse_format_specifier(const std::string& line) {
    if (line.size() < 2) {
        throw parse_exception("invalid format specifier line: " + line);
    }

    format_specifier_ = line; // Store the format specifier

    // Basic validation of format specifier
    if (format_specifier_.substr(0, 2) != "XL" && format_specifier_.substr(0, 2) != "XH" &&
        format_specifier_.substr(0, 2) != "XD" && format_specifier_.substr(0, 2) != "XQ") {
        throw parse_exception("unsupported format specifier: " + format_specifier_);
    }

    std::cout << "Format Specifier: " << format_specifier_ << '\n'; // Print for verification
}

rel_file::rel_file(const std::string& filename) : file_(filename) {
    if (!file_.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }
}

void rel_file::parse() {
    std::string line;
    bool first_line = true;

    while (std::getline(file_, line)) {
        if (first_line) {
            // Parse the format specifier on the first line
            parse_format_specifier(line);
            first_line = false;
        } else {
            // Parse the rest of the lines according to their type
            parse_line(line);
        }
    }
}

void rel_file::parse_line(const std::string& line) {
    switch (determine_line_type(line)) {
        case line_type::header:
            parse_header_line(line);
            break;
        case line_type::symbol:
            parse_symbol_line(line);
            break;
        case line_type::area:
            parse_area_line(line);
            break;
        case line_type::text:
            parse_text_line(line);
            break;
        case line_type::relocation:
            parse_relocation_line(line);
            break;
        case line_type::paging:
            parse_paging_line(line);
            break;
        default:
            throw parse_exception("unknown line type: " + line);
    }
}

line_type rel_file::determine_line_type(const std::string& line) const {
    if (line.empty()) return line_type::unknown;
    switch (line[0]) {
        case 'H': return line_type::header;
        case 'S': return line_type::symbol;
        case 'A': return line_type::area;
        case 'T': return line_type::text;
        case 'R': return line_type::relocation;
        case 'P': return line_type::paging;
        default: return line_type::unknown;
    }
}

void rel_file::parse_header_line(const std::string& line) {
    std::istringstream iss(line.substr(1)); // Skip the 'H'
    uint16_t areas, symbols;
    std::string temp;

    // Parse the header values, ignoring descriptive words
    if (!(iss >> areas >> temp >> temp >> symbols >> temp >> temp)) {
        throw parse_exception("invalid header line: " + line);
    }

    header_.areas = areas;
    header_.symbols = symbols;
}


void rel_file::parse_symbol_line(const std::string& line) {
    symbol sym;
    std::istringstream iss(line.substr(1));
    std::string type;
    if (!(iss >> sym.name >> type >> std::hex >> sym.value)) {
        throw parse_exception("invalid symbol line: " + line);
    }
    sym.is_definition = (type == "Def");
    symbols_.push_back(sym);
}

void rel_file::parse_area_line(const std::string& line) {
    area ar;
    std::istringstream iss(line.substr(1));
    if (!(iss >> ar.label >> std::hex >> ar.size >> std::hex >> ar.flags)) {
        throw parse_exception("invalid area line: " + line);
    }
    areas_.push_back(ar);
}

void rel_file::parse_text_line(const std::string& line) {
    text_line text;
    std::istringstream iss(line.substr(1));
    uint16_t byte;
    if (!(iss >> std::hex >> text.offset)) {
        throw parse_exception("invalid text line: " + line);
    }
    while (iss >> std::hex >> byte) {
        text.data.push_back(static_cast<uint8_t>(byte));
    }
    text_lines_.push_back(text);
}

void rel_file::parse_relocation_line(const std::string& line) {
    relocation rel;
    std::istringstream iss(line.substr(1));
    if (!(iss >> rel.area_index >> rel.mode >> rel.data_index >> std::hex >> rel.reference_index)) {
        throw parse_exception("invalid relocation line: " + line);
    }
    relocations_.push_back(rel);
}

void rel_file::parse_paging_line(const std::string& line) {
    paging pg;
    std::istringstream iss(line.substr(1));
    if (!(iss >> pg.area_index >> pg.mode >> pg.page_index >> std::hex >> pg.page_reference)) {
        throw parse_exception("invalid paging line: " + line);
    }
    pagings_.push_back(pg);
}

} // namespace rel_parser
