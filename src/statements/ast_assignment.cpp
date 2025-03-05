#include "../../include/statements/ast_assignment.hpp"
namespace ast{
void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)dest_reg;
    Variable variable_specs = context.get_variable(GetIdentifier());
    Type type = variable_specs.get_type();
    int offset = variable_specs.get_offset();
    context.push_operation_type(type);

    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    stream << context.store_instr(type) << " " << reg << ", " << offset << "(sp)" << std::endl;
    context.deallocate_register(reg);
    context.pop_operation_type();
}

void Assignment::Print(std::ostream &stream) const
{
    unary_expression_->Print(stream);
    stream << " = ";
    expression_->Print(stream);
    stream << ";" << std::endl;
}

std::string Assignment::GetIdentifier() const
{
    const Identifier *identifier = dynamic_cast<const Identifier *>(unary_expression_.get());
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    throw std::runtime_error("Assignment GetIdentifier: Not an identifier");
}

}
