#ifndef FRONTEND_INCLUDE_LEXER_HPP
#define FRONTEND_INCLUDE_LEXER_HPP

#include <string>

#include "parser.hpp"

#ifndef yyFlexLexer
    #include <FlexLexer.h>
#endif

namespace language {

class Lexer : public yyFlexLexer {
public:
  using yyFlexLexer::yyFlexLexer; 

  int yylex(yy::parser::value_type* yylval, yy::location* yylloc);
};

} // namespace language

int yylex(yy::parser::value_type* yylval,
          yy::location* yylloc,
          language::Lexer* scanner);

#endif // FRONTEND_INCLUDE_LEXER_HPP
