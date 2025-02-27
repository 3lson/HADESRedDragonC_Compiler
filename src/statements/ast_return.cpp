#include "../../include/statements/ast_return.hpp"
namespace ast{
void ReturnStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    (void)passed_reg;
    std::string return_register = context.get_return_register();
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context, return_register);
    }
    stream << "ret" << std::endl;
}

void ReturnStatement::Print(std::ostream &stream) const
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
