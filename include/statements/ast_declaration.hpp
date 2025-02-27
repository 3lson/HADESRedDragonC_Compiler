#pragma once

#include "../ast_node.hpp"
#include "../types/ast_type_specifier.hpp"
#include "../symbols/ast_identifier.hpp"
#include "ast_assignment.hpp"

namespace ast{

class Declaration : public Node
{
private:
    NodePtr type_specifier_;
    NodePtr declarator_list_;

public:
    Declaration(NodePtr type_specifier, NodePtr declarator_list) : type_specifier_(std::move(type_specifier)), declarator_list_(std::move(declarator_list)) {}
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;
};

}//namespace at
