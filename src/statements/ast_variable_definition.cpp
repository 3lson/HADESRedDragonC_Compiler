#include "../../include/statements/ast_variable_definition.hpp"

namespace ast {

void VariableDefinition::EmitRISC(std::ostream& stream, Context& context) const
{

    context.SetinitFlag();
    identifier_->EmitRISC(stream,context);
    context.ResetinitFlag();
}

void VariableDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";
    identifier_->Print(stream);

}

} // namespace ast
