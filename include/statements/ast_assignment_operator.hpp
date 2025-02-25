#pragma once

#include "ast_node.hpp"
#include "../types/ast_type_specifier.hpp"

namespace ast {

class AssignmentOperator: public Node
{
private:
    NodePtr value_;
    NodePtr identifier_;
public:
    AssignmentOperator(NodePtr value, NodePtr identifier) : value_(std::move(value)), identifier_(std::move(identifier)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
