#pragma once

#include "ast_node.hpp"
#include "../types/ast_type_specifier.hpp"

namespace ast {

class VariableDefinition : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr identifier_;
public:
    VariableDefinition(TypeSpecifier declaration_specifiers, NodePtr identifier) : declaration_specifiers_(declaration_specifiers), identifier_(std::move(identifier)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
