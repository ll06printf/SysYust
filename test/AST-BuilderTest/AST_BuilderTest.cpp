//
// Created by LL06p on 24-7-15.
//
#include <utility>
#include <filesystem>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include <range/v3/range.hpp>
#include <range/v3/view.hpp>

#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>

#include "SysYLexer.h"
#include "SysYParser.h"

#include "AST/SyntaxTreeBuilder.h"
#include "AST/SyntaxTreeString.h"
#include "utility/Logger.h"
#include "utility/StreamLogger.h"

namespace fs = std::filesystem;
//namespace ranges = std::ranges;
namespace views = ranges::views;

using namespace std::literals::string_literals;

int main(int argc, char *argv[]) {
    fs::create_directories("output");
    fs::path output_dir("output");
    fs::path input_file;
    if (argc == 2) {
        input_file = argv[1];
    } else {
        throw std::invalid_argument("Use command line to specify the input file");
    }

    std::ifstream input_stream(input_file);

    auto output_file = output_dir / input_file.stem().concat(".AST_Build.txt");
    auto log_file = output_dir / input_file.stem().concat(".AST_Builder.log");
    std::ofstream output_stream(output_file, std::ios::trunc);
    std::ofstream log_stream(log_file, std::ios::trunc);
    SysYust::Logger::setLogger(new SysYust::StreamLogger(log_stream));


    antlr4::ANTLRInputStream antlr_input(input_stream);
    SysYLexer lexer(&antlr_input);
    antlr4::CommonTokenStream token_stream(&lexer);
    SysYParser parser(&token_stream);
    auto tree = parser.compUnit();

    auto ASTree = SysYust::AST::SyntaxTreeBuilder::getTree(tree);
    SysYust::AST::SyntaxTreeString formatted_tree(*ASTree);

    output_stream << static_cast<std::string>(formatted_tree) << std::endl;

}