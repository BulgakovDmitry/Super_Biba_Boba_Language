#include "node.hpp"
#include "parser.hpp"
#include "simulator.hpp"
#include <fstream>
#include <iostream>
#include <memory>

extern int yylex();
yy::parser::semantic_type* yylval = nullptr;

int main(int argc, char* argv[]) {
    std::cout << "Run program\n";
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <program_file>\n";
        return 1;
    }

    std::ifstream program_file(argv[1]);
    if (!program_file) {
        std::cerr << "Cannot open program file\n";
        return 1;
    }

    std::unique_ptr<language::Program> root;

    std::cout << "Start parse\n";
    yy::parser parser{root};

    int result = parser.parse();
    program_file.close();

    if (result == 0 && root) {
        std::cout << "Parse OK\n";
    } else {
        std::cerr << "Parse failed\n";
    }

    language::Simulator simulator{};

    try {
        root->accept(simulator);
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }

    return result;
}
