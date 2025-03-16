#include "../../include/functions/ast_function_invocation.hpp"

namespace ast{

void FunctionInvocation::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    const std::string func_name = dynamic_cast<const Identifier*>(identifier_.get())->GetIdentifier();
    context.push_registers(stream);
    context.push_function_call(func_name);

    if (argument_list_ != nullptr)
    {
        dynamic_cast<const ExpressionList *>(argument_list_.get())->GetArguments(stream, context, dest_reg);
    }

    context.push_operation_type(GetType(context));

    stream << "call " << func_name << std::endl;
    stream << context.move_instr(context.get_function_call().get_return_value().get_type()) << " " << dest_reg << ", " << context.get_return_register() << std::endl;
    context.pop_operation_type();
    context.pop_function_call();
    context.pop_registers(stream);
}

void FunctionInvocation::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    stream << "(";
    if (argument_list_ != nullptr)
    {
        argument_list_->Print(stream);
    }
    stream << ")";
}

Type FunctionInvocation::GetType(Context &context) const
{
    const std::string func_name = dynamic_cast<const Identifier*>(identifier_.get())->GetIdentifier();
    Function function = context.get_function(func_name);
    return function.get_return_value().get_type();
}

bool FunctionInvocation::isPointerOp(Context &context) const
{
    Function function = context.get_function(dynamic_cast<const Identifier *>(identifier_.get())->GetIdentifier());
    return function.get_return_value().is_pointer();
}


}
