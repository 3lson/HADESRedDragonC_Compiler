#include "../../include/symbols/ast_identifier.hpp"
namespace ast{
void Identifier::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Variable variable = context.get_variable(identifier_);
    Type type = variable.get_type();

    if (variable.get_scope() == ScopeLevel::LOCAL){
        int offset = variable.get_offset();
        stream << context.load_instr(type) << " " << dest_reg << ", " << offset << "(sp)" << std::endl;
    }
    else if (variable.get_scope() == ScopeLevel::GLOBAL)
    {
        std::string global_memory_location = "global_" + identifier_;
        std::string global_memory_register = context.get_register(Type::_INT);

        stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
        stream << context.load_instr(type) << " " << dest_reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
        context.deallocate_register(global_memory_register);
    }

    else
    {
        throw std::runtime_error("Identifier EmitRISC: Invalid scope");
    }
}

void Identifier::Print(std::ostream &stream) const
{
    stream << identifier_;
};

std::string Identifier::GetIdentifier() const
{
    return identifier_;
}

Type Identifier::GetType(Context &context) const
{
    return context.get_variable(identifier_).get_type();
}
}
