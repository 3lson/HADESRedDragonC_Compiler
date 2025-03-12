#pragma once

#include "../ast_node.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../arrays/ast_array_declaration.hpp"
#include "../arrays/ast_array_initialization.hpp"
#include "../arrays/ast_array_index_access.hpp"
#include "../symbols/ast_constant.hpp"
#include "../ast_direct_declarator.hpp"

namespace ast {

class Assignment : public Node
{
private:
    NodePtr unary_expression_;
    NodePtr expression_;

public:
    Assignment(NodePtr unary_expression, NodePtr expression) : unary_expression_(std::move(unary_expression)), expression_(std::move(expression)) {}

    std::string GetIdentifier() const;

    int GetArraySize(Context &context) const;
    bool isArrayInitialization() const;

    void InitializeGlobals(std::ostream &stream, Context &context, Global &global) const;

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;

};

}//namespace ast
