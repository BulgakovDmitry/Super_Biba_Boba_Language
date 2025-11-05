#ifndef FRONTEND_INCLUDE_PARSER_HPP
#define FRONTEND_INCLUDE_PARSER_HPP

#include "node.hpp"
#include "token.hpp"
#include <memory>
#include <vector>

namespace language {

// Program     ::= StmtList
// StmtList    ::= Statement ';'
//
// Statement   ::= Assignment | IfStmt  | WhileStmt |  Input   | Print
//
// IfStmt      ::= 'if'    '(' Expression ')' '{' StmtList '}'
// WhileStmt   ::= 'while' '(' Expression ')' '{' StmtList '}'
//
// Assignment  ::= Var '=' Expression
//
// Input       ::= Var '=' '?'
// Print       ::= 'print' Expression
//
// Expression  ::= Equality
// Equality    ::= Rel ( ( '==' | '!=' ) Rel )*
// Rel         ::= AddSub ( ( '<' | '>' | '<=' | '>=' ) AddSub )*
// AddSub      ::= Primary ( ( '+' | '-' ) Primary )*
// Primary     ::= '(' Expression ')'| Var | Number
//
// Var         ::= ([a-z] | [A-Z])+
// Num         ::= ['0'-'9']+

class Parser {
    std::size_t pc_ = 0;
    std::unique_ptr<Node> root_{nullptr};

  public:
    Parser() = default;

    bool parse(const std::vector<std::unique_ptr<Token>> &tokens);

  private:
    std::unique_ptr<Node> get_operator(const std::vector<std::unique_ptr<Token>> &tokens);
};

inline bool Parser::parse(const std::vector<std::unique_ptr<Token>> &tokens) {
    auto root_ = std::make_unique<Statement_node>();

    root_->set_left(get_operator(tokens));
    root_->set_right(std::make_unique<Statement_node>());

    auto current_node = static_cast<Statement_node*>(root_->right_.get());
    if (!current_node) {
        throw std::runtime_error("Expected Statement_node");
    }

    while (true) {
        current_node->set_left(get_operator(tokens));
        current_node->set_right(std::make_unique<Statement_node>());
        auto current_node = current_node->right_.get();
    }

    return true;
}

} // namespace language

#endif // FRONTEND_INCLUDE_PARSER_HPP
