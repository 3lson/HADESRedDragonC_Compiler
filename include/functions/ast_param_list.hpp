#pragma once

#include "ast_node.hpp"
#include "../context/ast_context.hpp"

namespace ast {

using NodePtr = std::unique_ptr<const Node>; //a smart pointer to a node

class ParamList : public Node
{
private:
    std::vector<NodePtr> nodes_;

public:
    ParamList(NodePtr first_node) { nodes_.push_back(std::move(first_node)); }

    void PushBack(NodePtr item);
    virtual void EmitRISC(std::ostream& stream, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;
};

} // namespace ast
