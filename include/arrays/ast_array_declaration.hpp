#pragma once

#include "../ast_node.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../symbols/ast_constant.hpp"

namespace ast{

class ArrayDeclaration : public Node{
private:
    NodePtr identifier_;
    NodePtr constant_expression_;

public:
    ArrayDeclaration(NodePtr identifier, NodePtr constant_expression) : identifier_(std::move(identifier)), constant_expression_(std::move(constant_expression)) {}

    ArrayDeclaration(NodePtr identifier) : identifier_(std::move(identifier)), constant_expression_(nullptr) {}

    std::string GetIdentifier() const;
    int GetArraySize(Context &context) const;

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const;
    void Print(std::ostream& stream) const;
};

}
