#include "ast_compound_statements.hpp"

namespace ast {

void CompoundStatements::EmitRISC(std::ostream& stream, Context& context) const
{
    //Don't increment for while loops but need to check if this would not work for nested whiles
    context.IncrementscopeLevel();
    statements_->EmitRISC(stream, context);
    context.DecrementscopeLevel();
}

void CompoundStatements::Print(std::ostream& stream) const
{
    statements_->Print(stream);
}

} // namespace ast
