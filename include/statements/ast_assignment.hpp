#pragma once

#include "../ast_node.hpp"
#include "../symbols/ast_identifier.hpp"

namespace ast {

class AssignmentList : public NodeList
{
public:
    using NodeList::NodeList;
    ~AssignmentList() {}

};

class Assignment : public Node
{
private:
    NodePtr unary_expression_;
    NodePtr expression_;

public:
    Assignment(NodePtr unary_expression, NodePtr expression) : unary_expression_(std::move(unary_expression)), expression_(std::move(expression)) {}
    std::string GetIdentifier() const;

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;

};

}//namespace ast
