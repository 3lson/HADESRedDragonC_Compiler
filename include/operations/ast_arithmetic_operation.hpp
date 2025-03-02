#pragma once

#include "ast_node.hpp"
#include "ast_operand.hpp"

namespace ast{

enum class ArithOp {
    ADD, SUB, MUL, DIV, MOD,
};

class ArithExpression : public Operand{
private:
    ArithOp op_;
    NodePtr left_;
    NodePtr right_;

public:
    ArithExpression(ArithOp op, NodePtr left, NodePtr right) : op_(op), left_(std::move(left)), right_(std::move(right)) {}

    Type GetType(Context& context) const;
    std::string GetOperation(Type type) const;
    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override;
    void Print(std::ostream& stream) const override;

};

}//namespace ast
