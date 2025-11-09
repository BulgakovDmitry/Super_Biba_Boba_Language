#include <memory>
#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "bridge.hpp"

int yyFlexLexer::yywrap() { return 1; }

int main() {
    language::Lexer scanner(&std::cin, &std::cout);
    while (true) {
        int tok = scanner.yylex();
        if (tok == 0) { std::cout << "EOF\n"; break; }
        if (tok < 0) { std::cerr << "Lex error\n"; return 1; }
        scanner.print_current();
    }
    return 0;
}