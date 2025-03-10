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
    Variable variable = context.get_variable(GetIdentifier());

    Type type = GetType(context);

    std::string index_register = context.get_register(Type::_INT);
    GetIndex(stream, context, index_register, type);

    if (variable.get_scope() ==ScopeLevel::LOCAL){
        stream << "add " << index_register << ", " << index_register << ", sp" << std::endl;
        stream << context.load_instr(type) << " " << dest_reg << ", " << variable.get_offset() << "(" << index_register << ")" << std::endl;
    }
    else if(variable.get_scope() == ScopeLevel::GLOBAL){
        std::string global_memory_location = "global_" + GetIdentifier();
        std::string global_memory_register = context.get_register(Type::_INT);

        stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
        stream << "add " << global_memory_register << ", " << global_memory_register << ", " << index_register << std::endl;
        stream << context.load_instr(type) << " " << dest_reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;

        context.deallocate_register(global_memory_register);
    }

    context.deallocate_register(index_register);
}

void ArrayIndexAccess::GetIndex(std::ostream &stream, Context &context, std::string dest_reg, Type type) const
{
    // Set operation type as dealing with pointers
    context.push_operation_type(Type::_INT);

    // Emit index to specified register
    index_->EmitRISC(stream, context, dest_reg);

    stream << "slli " << dest_reg << ", " << dest_reg << ", " << types_mem_shift.at(type) << std::endl;

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
    Variable variable = context.get_variable(GetIdentifier());
    return variable.get_type();
}
}//namespace ast
