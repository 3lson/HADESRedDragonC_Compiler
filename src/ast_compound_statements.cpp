#include "ast_compound_statements.hpp"

namespace ast {

void CompoundStatements::EmitRISC(std::ostream& stream, Context& context) const
{
    context.IncrementscopeLevel();
    statements_->EmitRISC(stream, context);
    context.DecrementscopeLevel();
}

void CompoundStatements::Print(std::ostream& stream) const
{
    statements_->Print(stream);
}

} // namespace ast
