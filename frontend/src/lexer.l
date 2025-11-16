%option c++
%option noyywrap
%option nounput
%option noinput
%option batch

%{
  #include <string>
  #include <iostream>
  #include "parser.hpp"

  int yylineno;

  extern yy::parser::semantic_type* yylval;
%}

WHITESPACE    [ \t\r\v]+
ID            [a-zA-Z_][a-zA-Z0-9_]*
NUMBER        [0-9]+
LINE_COMMENT  "//".*
BLOCK_COMMENT "/*"([^*]|\*+[^*/])*\*+"/"
NEWLINE  \n

%%

{WHITESPACE}    { /* skip blanks and tabs */ }
{NEWLINE}       { ++yylineno; }

{LINE_COMMENT}  { /* skip */ }
{BLOCK_COMMENT} { /* skip */ }

"if"            { return yy::parser::token::TOK_IF; }
"else"          { return yy::parser::token::TOK_ELSE; }
"while"         { return yy::parser::token::TOK_WHILE; }
"print"         { return yy::parser::token::TOK_PRINT; }
"?"             { return yy::parser::token::TOK_INPUT; }

"=="            { return yy::parser::token::TOK_EQ; }
"!="            { return yy::parser::token::TOK_NEQ; }
"<="            { return yy::parser::token::TOK_LESS_OR_EQ; }
">="            { return yy::parser::token::TOK_GREATER_OR_EQ; }
"="             { return yy::parser::token::TOK_ASSIGN; }

"+"             { return yy::parser::token::TOK_PLUS; }
"-"             { return yy::parser::token::TOK_MINUS; }
"*"             { return yy::parser::token::TOK_MUL; }
"/"             { return yy::parser::token::TOK_DIV; }

"<"             { return yy::parser::token::TOK_LESS; }
">"             { return yy::parser::token::TOK_GREATER; }

"("             { return yy::parser::token::TOK_LEFT_PAREN; }
")"             { return yy::parser::token::TOK_RIGHT_PAREN; }
"{"             { return yy::parser::token::TOK_LEFT_BRACE; }
"}"             { return yy::parser::token::TOK_RIGHT_BRACE; }
";"             { return yy::parser::token::TOK_SEMICOLON; }

{NUMBER}        {
  if (yylval) {
    yylval->emplace<int>(std::stoi(yytext));
  } else {
    std::cerr << "ERROR: yylval is null!" << std::endl;
  }
  return yy::parser::token::TOK_NUMBER;
}

{ID}            {
  if (yylval) {
    yylval->emplace<std::string>(yytext);
  } else {
    std::cerr << "ERROR: yylval is null!" << std::endl;
  }
  return yy::parser::token::TOK_ID;
}

.               {
  std::cerr << "Unknown token: '" << yytext << "' at line " << yylineno << std::endl;;
  return -1;
}

<<EOF>>         { return 0; }

%%

