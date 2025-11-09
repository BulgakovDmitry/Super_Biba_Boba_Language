#ifndef FRONTEND_INCLUDE_LEXER_HPP
#define FRONTEND_INCLUDE_LEXER_HPP

#include <string>
#include <iostream>
#include "tokens.hpp"

#ifndef yyFlexLexer
    #include <FlexLexer.h>
#endif

namespace language {

class Lexer : public yyFlexLexer {
public:
    std::string current_lexem;
    std::string current_value;

    int process_if() {
        current_lexem = "conditional operator";
        current_value = "if";
        return static_cast<int>(Token_type::TOK_IF);
    }

    int process_else() {
        current_lexem = "conditional operator";
        current_value = "else";
        return static_cast<int>(Token_type::TOK_ELSE);
    }

    int process_while() {
        current_lexem = "conditional operator";
        current_value = "while";
        return static_cast<int>(Token_type::TOK_WHILE);
    }

    int process_print() {
        current_lexem = "operator";
        current_value = "print";
        return static_cast<int>(Token_type::TOK_PRINT);
    }

    int process_input() {
        current_lexem = "operator";
        current_value = "?";
        return static_cast<int>(Token_type::TOK_INPUT);
    }

    int process_plus() {
        current_lexem = "binary operator";
        current_value = "+";
        return static_cast<int>(Token_type::TOK_PLUS);
    }

    int process_minus() {
        current_lexem = "binary operator";
        current_value = "-";
        return static_cast<int>(Token_type::TOK_MINUS);
    }

    int process_mul() {
        current_lexem = "binary operator";
        current_value = "*";
        return static_cast<int>(Token_type::TOK_MUL);
    }

    int process_div()  {
        current_lexem = "binary operator";
        current_value = "/";
        return static_cast<int>(Token_type::TOK_DIV);
    }

    int process_assign() {
        current_lexem = "binary operator";
        current_value = "=";
        return static_cast<int>(Token_type::TOK_ASSIGN);
    }

    int process_eq()  {
        current_lexem = "comparing operator";
        current_value = "==";
        return static_cast<int>(Token_type::TOK_EQ);
    }

    int process_not_eq()  {
        current_lexem = "comparing operator";
        current_value = "!=";
        return static_cast<int>(Token_type::TOK_NOT_EQ);
    }

    int process_less()  {
        current_lexem = "comparing operator";
        current_value = "<";
        return static_cast<int>(Token_type::TOK_LESS);
    }

    int process_greater() {
        current_lexem = "comparing operator";
        current_value = ">";
        return static_cast<int>(Token_type::TOK_GREATER);
    }

    int process_less_or_eq() {
        current_lexem = "comparing operator";
        current_value = "<=";
        return static_cast<int>(Token_type::TOK_LESS_OR_EQ);
    }

    int process_greater_or_eq() {
        current_lexem = "comparing operator";
        current_value = ">=";
        return static_cast<int>(Token_type::TOK_GREATER_OR_EQ);
    }

    int process_left_paren() {
        current_lexem = "identifier";
        current_value = "(";
        return static_cast<int>(Token_type::TOK_LEFT_PAREN);
    }

    int process_right_paren() {
        current_lexem = "identifier";
        current_value = ")";
        return static_cast<int>(Token_type::TOK_RIGHT_PAREN);
    }

    int process_left_brace() {
        current_lexem = "identifier";
        current_value = "{";
        return static_cast<int>(Token_type::TOK_LEFT_BRACE);
    }

    int process_right_brace() {
        current_lexem = "identifier";
        current_value = "}";
        return static_cast<int>(Token_type::TOK_RIGHT_BRACE);
    }

    int process_semicolon() {
        current_lexem = "identifier";
        current_value = ";";
        return static_cast<int>(Token_type::TOK_SEMICOLON);
    }

    int process_id() {
        current_lexem = "variable";
        current_value = yytext;
        return static_cast<int>(Token_type::TOK_ID);
    }

    int process_number() {
        current_lexem = "number";
        current_value = yytext;
        return static_cast<int>(Token_type::TOK_NUMBER);
    }

  using yyFlexLexer::yyFlexLexer;

  int yylex() override;

  void print_current() const {
      std::cout << current_lexem << " <" << current_value << ">" << std::endl;
  }
};

} // namespace language

#endif // FRONTEND_INCLUDE_LEXER_HPP
