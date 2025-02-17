#include "ast_assignment_operator.hpp"

namespace ast {

void AssignmentOperator::EmitRISC(std::ostream& stream, Context& context) const
{
    context.SetassignFlag();
    identifier_->EmitRISC(stream, context);
    value_->EmitRISC(stream, context);
    stream << std::endl;
    context.ResetassignFlag();

}

void AssignmentOperator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
    stream << " = ";
    value_->Print(stream);
    stream << " ;" << std::endl;
}

} // namespace ast
