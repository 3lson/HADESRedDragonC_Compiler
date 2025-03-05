#pragma once

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

namespace ast{

class ExpressionList : public NodeList
{
public:
    using NodeList::NodeList;
    ~ExpressionList() = default;

    void GetArguments(std::ostream &stream, Context &context, std::string dest_reg) const;
    void Print(std::ostream &stream) const override;
};

}
