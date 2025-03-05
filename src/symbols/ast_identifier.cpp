#include "../../include/symbols/ast_identifier.hpp"
namespace ast{
void Identifier::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Variable variable_specs = context.get_variable(identifier_);
    Type type = variable_specs.get_type();
    int offset = variable_specs.get_offset();

    stream << context.load_instr(type) << " " << dest_reg << ", " << offset << "(sp)" << std::endl;
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
