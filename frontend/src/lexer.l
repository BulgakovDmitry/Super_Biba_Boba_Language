%option c++
%option noyywrap
%option nounput noinput

%{
  #include <string>
  #include <iostream>

  #include "parser.hpp"  
  #include "lexer.hpp"

  using token          = yy::parser::token;
  using semantic_type  = yy::parser::semantic_type;
  using location_type  = yy::parser::location_type;

  #undef  YY_DECL
  #define YY_DECL int language::Lexer::yylex(semantic_type* yylval, location_type* yylloc)
  #define YY_USER_ACTION yylloc->columns(yyleng);
%}

WHITESPACE    [ \t\r\v\n]+
ID            [a-zA-Z_][a-zA-Z0-9_]*
NUMBER        [0-9]+
LINE_COMMENT  "//".*
BLOCK_COMMENT "/*"([^*]|\*+[^*/])*\*+"/"

%%

{WHITESPACE}    { /* skip */ }
\n              { yylloc->lines(1); yylloc->step(); }

{LINE_COMMENT}  { /* skip */ }
{BLOCK_COMMENT} { /* skip */ }

"if"            { return token::TOK_IF; }
"else"          { return token::TOK_ELSE; }
"while"         { return token::TOK_WHILE; }
"print"         { return token::TOK_PRINT; }
"?"             { return token::TOK_INPUT; }

"=="            { return token::TOK_EQ; }
"!="            { return token::TOK_NEQ; }
"<="            { return token::TOK_LESS_OR_EQ; }
">="            { return token::TOK_GREATER_OR_EQ; }
"="             { return token::TOK_ASSIGN; }

"+"             { return token::TOK_PLUS; }
"-"             { return token::TOK_MINUS; }
"*"             { return token::TOK_MUL; }
"/"             { return token::TOK_DIV; }

"<"             { return token::TOK_LESS; }
">"             { return token::TOK_GREATER; }

"("             { return token::TOK_LEFT_PAREN; }
")"             { return token::TOK_RIGHT_PAREN; }
"{"             { return token::TOK_LEFT_BRACE; }
"}"             { return token::TOK_RIGHT_BRACE; }
";"             { return token::TOK_SEMICOLON; }

{NUMBER}        {
                    yylval->emplace<int>(std::stoi(yytext));
                    return token::TOK_NUMBER;
                }

{ID}            {
                    yylval->emplace<std::string>(yytext);
                    return token::TOK_ID;
                }

.               {
                    std::cerr << "Lexical error: unexpected char '" << yytext[0] << "'\n";
                    return token::YYerror;
                }

<<EOF>>         { return 0; }

%%

int yyFlexLexer::yylex() { return 0; }

int yylex(semantic_type* yylval, location_type* yylloc, language::Lexer* scanner) {
  return scanner->yylex(yylval, yylloc);
}