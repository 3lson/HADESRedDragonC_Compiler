#pragma once

#include "ast_node.hpp"

namespace ast{

enum class ArithOp {
    ADD, SUB, MUL, DIV, MODULO,
    BITWISE_AND, BITWISE_OR, BITWISE_XOR,
    EQUAL, NOT_EQUAL, LESS_THAN, GREATER_THAN,
    LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL,
    LOGICAL_AND, LOGICAL_OR,
    LEFT_SHIFT, RIGHT_SHIFT
};

class ArithExpression : public Node{
private:
    ArithOp op_;
    NodePtr left_;
    NodePtr right_;
    mutable std::string var_;
    void SetUniqueVarValue(Context& context, const std::string& basename) const;
    void OperationExecutor(std::ostream& stream, Context& context, const std::string& retret, const std::string& tempreg) const;

public:
    ArithExpression(ArithOp op, NodePtr left, NodePtr right) : op_(op), left_(std::move(left)), right_(std::move(right)), var_("") {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};


}//namespace ast
