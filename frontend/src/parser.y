%language "c++"
%defines
%locations
%nonassoc PREC_IFX
%nonassoc TOK_ELSE
%define api.value.type variant
%define parse.error verbose

%lex-param   { language::Lexer* scanner }
%parse-param { language::Lexer* scanner }

%code requires {
  #include <string>
  namespace language { class Lexer; }
}

%code {
  #include "lexer.hpp"
  #include <iostream>
}

%token TOK_IF TOK_ELSE TOK_WHILE TOK_PRINT TOK_INPUT
%token TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV
%token TOK_ASSIGN
%token TOK_EQ TOK_NEQ TOK_LESS TOK_GREATER TOK_LESS_OR_EQ TOK_GREATER_OR_EQ
%token TOK_LEFT_PAREN TOK_RIGHT_PAREN TOK_LEFT_BRACE TOK_RIGHT_BRACE TOK_SEMICOLON
%token <std::string> TOK_ID
%token <int>         TOK_NUMBER
%token TOK_EOF 0      

%start program

%%

program        : stmt_list ;

stmt_list      : /* empty */
               | stmt_list stmt
               ;

stmt           : assignment TOK_SEMICOLON
               | if_stmt
               | while_stmt
               | print_stmt TOK_SEMICOLON
               | block
               ;

block          : TOK_LEFT_BRACE stmt_list TOK_RIGHT_BRACE ;

assignment     : TOK_ID TOK_ASSIGN expr ;

if_stmt
               : TOK_IF TOK_LEFT_PAREN expr TOK_RIGHT_PAREN stmt %prec PREC_IFX
               | TOK_IF TOK_LEFT_PAREN expr TOK_RIGHT_PAREN stmt TOK_ELSE stmt
               ;
 
while_stmt     : TOK_WHILE TOK_LEFT_PAREN expr TOK_RIGHT_PAREN stmt ;

print_stmt     : TOK_PRINT expr ;

expr           : equality ;

equality       : relational
               | equality TOK_EQ  relational
               | equality TOK_NEQ relational
               ;

relational     : additive
               | relational TOK_LESS          additive
               | relational TOK_LESS_OR_EQ    additive
               | relational TOK_GREATER       additive
               | relational TOK_GREATER_OR_EQ additive
               ;

additive       : multiplicative
               | additive TOK_PLUS  multiplicative
               | additive TOK_MINUS multiplicative
               ;

multiplicative : unary
               | multiplicative TOK_MUL unary
               | multiplicative TOK_DIV unary
               ;

unary          : TOK_MINUS unary
               | primary
               ;

primary        : TOK_NUMBER
               | TOK_ID
               | TOK_LEFT_PAREN expr TOK_RIGHT_PAREN
               | TOK_INPUT             
               ;
%%

void yy::parser::error(const yy::parser::location_type& l, const std::string& m) {
  std::cerr << "Syntax error: " << m << " at " << l << "\n";
}
