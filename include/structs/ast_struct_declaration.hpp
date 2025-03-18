#pragma once

#include "ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../context/ast_context.hpp"

namespace ast{

class StructDeclaration : public Node{
private:
    NodePtr specifiers_;
    NodePtr declarators_;

public:
    StructDeclaration(NodePtr specifiers, NodePtr declarators) : specifiers_(std::move(specifiers)), declarators_(std::move(declarators)) {}

    void Print(std::ostream& stream) const override;
    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override;
};

}//namespace ast
