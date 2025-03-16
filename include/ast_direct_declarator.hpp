#pragma once

#include "ast_node.hpp"
#include "symbols/ast_identifier.hpp"
#include "functions/ast_parameter_definition.hpp"
#include "arrays/ast_array_declaration.hpp"
#include "ast_declarator.hpp"

namespace ast{

class DirectDeclarator : public Declarator
{
private:
    NodePtr identifier_;
    NodePtr parameter_list_;

public:
    DirectDeclarator(NodePtr identifier) : identifier_(std::move(identifier)), parameter_list_(nullptr) {};
    DirectDeclarator(NodePtr identifier, NodePtr parameter_list) : identifier_(std::move(identifier)), parameter_list_(std::move(parameter_list)) {};

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const override;
    std::vector<Parameter>GetParameters(Context &context) const override;
    int GetDereference() const override;
    int GetOffset() const override;
    void StoreParameters (std::ostream &stream, Context &context, std::string dest_reg) const override;
    bool isPointer() const override;
};

}//namespace ast
