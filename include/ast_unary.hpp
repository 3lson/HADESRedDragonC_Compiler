#pragma once

#include "ast_node.hpp"

namespace ast {

enum class UnaryOp {
    PLUS,           // Unary plus (+)
    MINUS,          // Unary minus (-)
    BITWISE_NOT,    // Bitwise NOT (~)
    LOGICAL_NOT,     // Logical NOT (!)
    INCREMENT,      // (++)
    DECREMENT       // (--)
};

class UnaryExpression : public Node {
public:
    UnaryExpression(UnaryOp op, NodePtr operand) : op_(op), operand_(std::move(operand)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

private:
    UnaryOp op_;
    NodePtr operand_;
};

} // namespace ast

