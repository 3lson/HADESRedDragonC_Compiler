#include "../../include/symbols/ast_identifier.hpp"
namespace ast{
void Identifier::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    if (context.is_enum(identifier_))
    {
        stream << "li " << dest_reg << ", " << context.get_enum_label(identifier_) << std::endl;
    }
    else{
        Variable variable = context.get_variable(identifier_);
        Type type = variable.is_pointer() ? Type::_INT : variable.get_type();

        if (variable.get_scope() == ScopeLevel::LOCAL){
            int offset = variable.get_offset();
            stream << context.load_instr(type) << " " << dest_reg << ", " << offset << "(s0)" << std::endl;
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
    if (context.is_enum(identifier_)){
        return Type::_INT;
    }
    return context.get_variable(identifier_).get_type();
}

int Identifier::GetValue(Context &context) const{
    if(!context.is_enum(identifier_))
    {
        throw std::runtime_error("Identifier::GetValue - identifier is not an enum");
    }
    return context.get_enum_label(identifier_);
}

bool Identifier::isPointerOp(Context &context) const
{
    if (context.is_enum(identifier_)){
        return false;
    }
    return context.get_variable(identifier_).is_pointer();
}

}
