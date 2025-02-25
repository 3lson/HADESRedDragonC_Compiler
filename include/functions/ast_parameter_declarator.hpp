#pragma once

#include "ast_node.hpp"

namespace ast {

class ParameterDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr params_;

public:
    ParameterDeclarator(NodePtr identifier, NodePtr params) : identifier_(std::move(identifier)), params_(std::move(params)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
