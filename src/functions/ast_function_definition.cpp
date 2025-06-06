#include "../../include/functions/ast_function_definition.hpp"

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, Context& context) const
{

    context.SetfuncFlag();
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.
    stream << ".text" << std::endl;
    stream << ".globl f" << std::endl;


    declarator_->EmitRISC(stream, context); //traverses associated branch of tree

    if(context.GetparamFlag() == true){
        context.ResetparamFlag();
    }

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context);
    }
    context.ResetfuncFlag();

}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << " {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
