#ifndef FRONTEND_INCLUDE_SIMULATOR_HPP
#define FRONTEND_INCLUDE_SIMULATOR_HPP

#include "node.hpp"
#include <string>
#include <unordered_map>

namespace language {

class Simulator final: public ASTVisitor {
private:
    std::unordered_map<std::string, number_t> nametable;
public:
    Simulator() = default;
    bool simulate_run_program(Program &program) {
        for (auto &statement : program.statements) {
            if ()
        }

        return true;
    }

private:
    void visit(Program &node) override {

    };
    void visit(Assignment &node) override;
    void visit(BinaryOp &node) override;
    void visit(UnaryOp &node) override;
    void visit(Number &node) override;
    void visit(Variable &node) override;
};

} // namespace language

#endif // FRONTEND_INCLUDE_SIMULATOR_HPP
