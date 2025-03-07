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

    if (isArrayInitialization())
    {
        dynamic_cast<const ArrayInitialization*>(expression_.get())->SaveValue(stream, context, offset, type);
    }

    else
    {
        const Identifier *identifier = dynamic_cast<const Identifier *>(unary_expression_.get());
        const ArrayIndexAccess *array_index_access = dynamic_cast<const ArrayIndexAccess *>(unary_expression_.get());

        if (identifier != nullptr)
        {
            stream << context.store_instr(type) << " " << reg << ", " << offset << "(sp)" << std::endl;
        }

        // If array access, load expression into specific element by first evaluating index
        else if (array_index_access != nullptr)
        {
            std::string index_register = context.get_register(Type::_INT);
            array_index_access->GetIndex(stream, context, index_register, type);

            stream << context.store_instr(type) << " " << reg << ", " << variable_specs.get_offset() << "(" << index_register << ")" << std::endl;

            context.deallocate_register(index_register);
        }

        else
        {
            throw std::runtime_error("Assignment EmitRISC: Not an identifier or array access");
        }
    }

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
    const ArrayIndexAccess *array_index_access = dynamic_cast<const ArrayIndexAccess *>(unary_expression_.get());
    const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(unary_expression_.get());
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (array_index_access != nullptr)
    {
        return array_index_access->GetIdentifier();
    }
    else if (array_declaration != nullptr)
    {
        return array_declaration->GetIdentifier();
    }
    throw std::runtime_error("Assignment GetIdentifier: Not an identifier");
}

int Assignment::GetArraySize() const
{
    const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(unary_expression_.get());

    if (array_declaration != nullptr)
    {

        if (array_declaration->GetArraySize() == -1)
        {
            return dynamic_cast<const ArrayInitialization *>(expression_.get())->GetArraySize();
        }
        return array_declaration->GetArraySize();
    }

    return 1;
}

bool Assignment::isArrayInitialization() const
{
    return dynamic_cast<const ArrayDeclaration *>(unary_expression_.get()) != nullptr;
}

}
