#include "ast_direct_declarator.hpp"

namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    identifier_->EmitRISC(stream, context);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
    stream << " ( )" ;
}

} // namespace ast
