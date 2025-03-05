#include "../../include/symbols/ast_constant.hpp"
namespace ast{

void IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)context;
    stream << "li " << dest_reg << ", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type IntConstant::GetType(Context &context) const
{
    (void)context;
    return Type::_INT;
}

void FloatConstant::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    int label_number = context.registerConstant(value_);

    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.LC" << label_number << ")" << std::endl;
    stream << context.load_instr(Type::_FLOAT) << " " << dest_reg << ", %lo(.LC" << label_number << ")" << "(" << address_register << ")" << std::endl;
    context.deallocate_register(address_register);
}

void FloatConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type FloatConstant::GetType(Context &context) const
{
    (void)context;
    return Type::_FLOAT;
}

void DoubleConstant::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    int label_number = context.registerConstant(value_);

    std::string address_register = context.get_register(Type::_INT);
    stream << "lui " << address_register << ", %hi(.LC" << label_number << ")" << std::endl;
    stream << context.load_instr(Type::_DOUBLE) << " " << dest_reg << ", %lo(.LC" << label_number << ")" << "(" << address_register << ")" << std::endl;
    context.deallocate_register(address_register);
}

void DoubleConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

Type DoubleConstant::GetType(Context &context) const
{
    (void)context;
    return Type::_DOUBLE;
}


}
