#include "../../include/functions/ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, Context& context) const
{
    if (expression_ != nullptr)
    {
        context.SetretFlag();
        expression_->EmitRISC(stream, context);
    }
    stream << "ret" << std::endl;
    context.ResetretFlag();
}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
