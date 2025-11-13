%language "c++"
%defines "parser.hpp"
%locations
%define parse.error detailed
%define api.value.type variant

%nonassoc PREC_IFX
%nonassoc TOK_ELSE

%lex-param   { language::Lexer* scanner }
%parse-param { language::Lexer* scanner }

%code requires {
  #include <string>
  namespace language { class Lexer; }
}

%code {
  #include "lexer.hpp"
  #include <iostream>
  static int yylex(yy::parser::value_type*      /*yylval*/,
                   yy::parser::location_type*   /*yylloc*/,
                   language::Lexer*             scanner)
  {
      return scanner->yylex();
  }
}

/* ________________________Tokens________________________ */
/* --- Keywords --- */
%token TOK_IF            "if"
%token TOK_ELSE          "else"
%token TOK_WHILE         "while"
%token TOK_PRINT         "print"
%token TOK_INPUT         "?"

/* --- Arithmetic operators --- */
%token TOK_PLUS          "+"
%token TOK_MINUS         "-"
%token TOK_MUL           "*"
%token TOK_DIV           "/"

/* --- Assignment --- */
%token TOK_ASSIGN        "="

/* --- Comparison operators --- */
%token TOK_EQ            "=="
%token TOK_NEQ           "!="
%token TOK_LESS          "<"
%token TOK_GREATER       ">"
%token TOK_LESS_OR_EQ    "<="
%token TOK_GREATER_OR_EQ ">="

/* --- Parentheses and separators --- */
%token TOK_LEFT_PAREN    "("
%token TOK_RIGHT_PAREN   ")"
%token TOK_LEFT_BRACE    "{"
%token TOK_RIGHT_BRACE   "}"
%token TOK_SEMICOLON     ";"

/* --- Tokens with semantic values --- */
%token <std::string> TOK_ID     "identifier"
%token <int>         TOK_NUMBER "number"

/* --- End of file --- */
%token TOK_EOF 0
/* ______________________________________________________ */

%start program

%%

program        : stmt_list ;

stmt_list      : /* empty */
               | stmt_list statement
               ;

statement      : assignment TOK_SEMICOLON
               | input TOK_SEMICOLON
               | if_stmt
               | while_stmt
               | print_stmt TOK_SEMICOLON
               | block
               ;

block          : TOK_LEFT_BRACE stmt_list TOK_RIGHT_BRACE ;

assignment     : TOK_ID TOK_ASSIGN expr 
               ;

input          : TOK_ID TOK_ASSIGN TOK_INPUT
               ;

if_stmt        : TOK_IF TOK_LEFT_PAREN expr TOK_RIGHT_PAREN statement %prec PREC_IFX
               | TOK_IF TOK_LEFT_PAREN expr TOK_RIGHT_PAREN statement TOK_ELSE statement
               ;

while_stmt     : TOK_WHILE TOK_LEFT_PAREN expr TOK_RIGHT_PAREN statement ;

print_stmt     : TOK_PRINT expr ;

expr           : equality ;

equality       : relational
               | equality TOK_EQ  relational
               | equality TOK_NEQ relational
               ;

relational     : add_sub
               | relational TOK_LESS          add_sub
               | relational TOK_LESS_OR_EQ    add_sub
               | relational TOK_GREATER       add_sub
               | relational TOK_GREATER_OR_EQ add_sub
               ;

add_sub        : mul_div
               | add_sub TOK_PLUS  mul_div
               | add_sub TOK_MINUS mul_div
               ;

mul_div        : unary
               | mul_div TOK_MUL unary
               | mul_div TOK_DIV unary
               ;

unary          : TOK_MINUS unary
               | primary
               ;

primary        : TOK_NUMBER
               | TOK_ID
               | TOK_LEFT_PAREN expr TOK_RIGHT_PAREN
               ;
%%

void yy::parser::error(const location& l, const std::string& m) {
    std::cerr << "Syntax error at line " << l.begin.line
              << ", column " << l.begin.column << ": " << m << "\n";
}
