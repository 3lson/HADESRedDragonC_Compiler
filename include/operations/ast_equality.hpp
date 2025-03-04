#pragma once

#include "ast_node.hpp"
#include "ast_operand.hpp"

namespace ast{

enum class EqualityOp {
    EQUAL, NOT_EQUAL,
};

class EqualityExpression : public Operand{
private:
    EqualityOp op_;
    NodePtr left_;
    NodePtr right_;

public:
    EqualityExpression(EqualityOp op, NodePtr left, NodePtr right) : op_(op), left_(std::move(left)), right_(std::move(right)) {}

    Type GetType(Context& context) const;
    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override;
    void Print(std::ostream& stream) const override;

};

}//namespace ast
