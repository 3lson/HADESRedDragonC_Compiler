#include "../include/arrays/ast_array_index_access.hpp"

namespace ast{

std::string ArrayIndexAccess::GetIdentifier() const
{
    const Identifier *identifier = dynamic_cast<const Identifier *>(identifier_.get());
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    throw std::runtime_error("ArrayIndexAccess::GetIdentifier - not an identifier");
}

void ArrayIndexAccess::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());

    Type type = GetType(context);

    std::string index_register = context.get_register(Type::_INT);
    GetIndex(stream, context, index_register, type);

    stream << context.load_instr(type) << " " << dest_reg << ", " << variable_specs.get_offset() << "(" << index_register << ")" << std::endl;

    context.deallocate_register(index_register);
}

void ArrayIndexAccess::GetIndex(std::ostream &stream, Context &context, std::string dest_reg, Type type) const
{
    // Set operation type as dealing with pointers
    context.push_operation_type(Type::_INT);

    // Emit index to specified register
    index_->EmitRISC(stream, context, dest_reg);

    stream << "slli " << dest_reg << ", " << dest_reg << ", " << types_shift.at(type) << std::endl;

    stream << "add " << dest_reg << ", " << dest_reg << ", sp" << std::endl;

    context.pop_operation_type();
}

void ArrayIndexAccess::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    stream << "[";
    index_->Print(stream);
    stream << "]";
}

Type ArrayIndexAccess::GetType(Context &context) const
{
    Variable variable_specs = context.get_variable(GetIdentifier());
    return variable_specs.get_type();
}
}//namespace ast
