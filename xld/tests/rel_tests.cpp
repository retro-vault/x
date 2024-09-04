#include <gtest/gtest.h>
#include <rel_file.h>

TEST(rel_tests,init) {

    try {
        // Replace "sample.rel" with the path to an actual SDCC REL file for testing.
        rel_parser::rel_file parser("bin/data/abs.rel");
        parser.parse();

        // Display parsed header information
        const auto& header = parser.get_header();
        std::cout << "Header: Areas = " << header.areas 
                  << ", Symbols = " << header.symbols << '\n';

        // Display parsed symbols
        const auto& symbols = parser.get_symbols();
        std::cout << "\nSymbols:\n";
        for (const auto& sym : symbols) {
            std::cout << "Name: " << sym.name 
                      << ", Value: 0x" << std::hex << sym.value 
                      << ", Type: " << (sym.is_definition ? "Definition" : "Reference") << '\n';
        }

        // Display parsed areas
        const auto& areas = parser.get_areas();
        std::cout << "\nAreas:\n";
        for (const auto& area : areas) {
            std::cout << "Label: " << area.label 
                      << ", Size: 0x" << std::hex << area.size 
                      << ", Flags: 0x" << std::hex << static_cast<int>(area.flags) << '\n';
        }

        // Display parsed text lines
        const auto& text_lines = parser.get_text_lines();
        std::cout << "\nText Lines:\n";
        for (const auto& text : text_lines) {
            std::cout << "Offset: 0x" << std::hex << text.offset 
                      << ", Data: ";
            for (const auto& byte : text.data) {
                std::cout << std::hex << static_cast<int>(byte) << ' ';
            }
            std::cout << '\n';
        }

        // Display parsed relocations
        const auto& relocations = parser.get_relocations();
        std::cout << "\nRelocations:\n";
        for (const auto& rel : relocations) {
            std::cout << "Area Index: 0x" << std::hex << rel.area_index 
                      << ", Mode: 0x" << std::hex << static_cast<int>(rel.mode) 
                      << ", Data Index: 0x" << std::hex << static_cast<int>(rel.data_index) 
                      << ", Reference Index: 0x" << std::hex << rel.reference_index << '\n';
        }

        // Display parsed pagings
        const auto& pagings = parser.get_pagings();
        std::cout << "\nPaging Information:\n";
        for (const auto& pg : pagings) {
            std::cout << "Area Index: 0x" << std::hex << pg.area_index 
                      << ", Mode: 0x" << std::hex << static_cast<int>(pg.mode) 
                      << ", Page Index: 0x" << std::hex << static_cast<int>(pg.page_index) 
                      << ", Page Reference: 0x" << std::hex << pg.page_reference << '\n';
        }

    } catch (const rel_parser::parse_exception& e) {
        std::cerr << "Error parsing REL file: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
    }


}