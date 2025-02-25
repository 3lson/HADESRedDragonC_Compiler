#pragma once

#include "ast_node.hpp"

namespace ast {

class CompoundStatements : public Node
{
private:
    NodePtr statements_;

public:
    CompoundStatements(NodePtr statements) : statements_(std::move(statements)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
