#include "ast_parameter_declarator.hpp"

namespace ast {

void ParameterDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    context.SetparamFlag();
    identifier_->EmitRISC(stream, context);
    stream << ":" << std::endl;
    params_->EmitRISC(stream, context);
    //reseting performed inside FunctionDefinition
}

void ParameterDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
    stream << " ( " ;
    params_->Print(stream);
    stream << " ) " ;
}

} // namespace ast
