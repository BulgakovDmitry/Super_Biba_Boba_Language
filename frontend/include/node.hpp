#ifndef FRONTEND_INCLUDE_AST_HPP
#define FRONTEND_INCLUDE_AST_HPP

#include <memory>

namespace language {

class Node {
public:
    virtual ~Node() = default;
};

class Binary_operator_node : public Node {
    std::unique_ptr<Node> left_{nullptr};
    std::unique_ptr<Node> right_{nullptr};

    Binary_operator_node(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right)
        : left_(std::move(left)), right_(std::move(right)) {}
};

class Unary_operator_node : public Node {
    std::unique_ptr<Node> right_{nullptr};

    Unary_operator_node(std::unique_ptr<Node> &&right) : right_(std::move(right)) {}
};

class Statement_node : public Node {
  public:
    std::unique_ptr<Node> left_{nullptr};
    std::unique_ptr<Node> right_{nullptr};

    Statement_node() = default;
    Statement_node(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right)
        : left_(std::move(left)), right_(std::move(right)) {}

    void set_left(std::unique_ptr<Node> &&left) {
        left_ = std::move(left);
    }

    void set_right(std::unique_ptr<Node> &&right) {
        right_ = std::move(right);
    }
};

class Number_node : public Node {};

class Variable_node : public Node {};

} // namespace language

#endif // FRONTEND_INCLUDE_AST_HPP
