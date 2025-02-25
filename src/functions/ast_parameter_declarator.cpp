#include "../../include/functions/ast_parameter_declarator.hpp"

namespace ast {

void ParameterDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    context.SetparamFlag();
    context.IncrementscopeLevel();
    identifier_->EmitRISC(stream, context);
    stream << ":" << std::endl;
    params_->EmitRISC(stream, context);
    context.DecrementscopeLevel();
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
