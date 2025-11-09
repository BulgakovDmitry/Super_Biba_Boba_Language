#include <memory>
#include <fstream>
#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"

int main(int argc, char** argv) {  
    language::Lexer scanner(&std::cin, &std::cout);

    yy::parser parser(&scanner);

    int rc = parser.parse();
    if (rc == 0) std::cout << "Parse OK\n";
    return rc;
}