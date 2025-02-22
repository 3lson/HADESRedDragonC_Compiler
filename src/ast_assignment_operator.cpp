#include "ast_assignment_operator.hpp"

namespace ast {

void AssignmentOperator::EmitRISC(std::ostream& stream, Context& context) const
{
    //sets identifierassign Flag high indicating that the other operand is a variable as well
    context.SetassignFlag();
    context.SetequatingvarFlag();
    value_->EmitRISC(stream, context);
    context.ResetequatingvarFlag();

    identifier_->EmitRISC(stream, context);
    context.ResetexpressionassignFlag();
    context.SetequatingvarFlag();
    context.SetsecondcallFlag();
    value_->EmitRISC(stream, context);
    context.ResetsecondcallFlag();
    context.ResetequatingvarFlag();
    context.ResetidentifierassignFlag();
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
