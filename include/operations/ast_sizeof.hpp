#pragma once

#include "../ast_node.hpp"
#include "../specifiers/ast_type_specifier.hpp"
#include "ast_operand.hpp"

namespace ast{

class SizeOf : public Operand
{
private:
    NodePtr unary_expression_;

public:
    SizeOf(NodePtr unary_expression) : unary_expression_(std::move(unary_expression)) {}

    Type GetType(Context &context) const override;
    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;
    bool isPointerOp(Context &context) const override;
};

}//namespace ast