#include "../../include/statements/ast_expression_list.hpp"

namespace ast{

void ExpressionList::GetArguments(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)dest_reg;
    Function function = context.get_function_call();
    int int_reg = 10, float_reg = 42;
    int arg_reg_num;

    for (size_t arg = 0; arg < function.get_parameters().size(); ++arg)
    {
        switch(function.get_parameters()[arg].get_type())
        {
            case Type::_CHAR:
            case Type::_UNSIGNED_INT:
            case Type::_INT:
                arg_reg_num = int_reg++;
                break;
            case Type::_FLOAT:
            case Type::_DOUBLE:
                arg_reg_num = float_reg++;
                break;
            default:
                throw std::runtime_error("ExpressionList GetArguments: Unknown Type");
        }

        std::string arg_reg_name = context.get_register_name(arg_reg_num);
        dynamic_cast<const Operand*>(get_nodes()[arg].get())->EmitRISC(stream, context, arg_reg_name);
    }
}

void ExpressionList::Print(std::ostream &stream) const
{
    for (const auto& node : get_nodes())
    {
        if (!node){
            continue;
        }
        node->Print(stream);
        stream << ", ";
    }
    stream << std::endl;
}

}
