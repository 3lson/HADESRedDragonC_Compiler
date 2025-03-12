#include "../../include/statements/ast_assignment.hpp"
namespace ast{
void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)dest_reg;
    Variable variable = context.get_variable(GetIdentifier());
    Type type = variable.get_type();
    int offset = variable.get_offset();
    context.push_operation_type(type);

    std::string reg = context.get_register(type);
    expression_->EmitRISC(stream, context, reg);

    if (isArrayInitialization())
    {
        dynamic_cast<const ArrayInitialization*>(expression_.get())->SaveValue(stream, context, variable, GetIdentifier());
    }

    else
    {
        const Identifier *identifier = dynamic_cast<const Identifier *>(unary_expression_.get());
        const ArrayIndexAccess *array_index_access = dynamic_cast<const ArrayIndexAccess *>(unary_expression_.get());

        if (identifier != nullptr)
        {
            if (variable.get_scope() == ScopeLevel::LOCAL)
            {
                stream << context.store_instr(type) << " " << reg << ", " << offset << "(sp)" << std::endl;
            }

            else if (variable.get_scope() == ScopeLevel::GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << context.store_instr(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;
                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in Identifier");
            }
        }

        // If array access, load expression into specific element by first evaluating index
        else if (array_index_access != nullptr)
        {
            std::string index_register = context.get_register(Type::_INT);
            array_index_access->GetIndex(stream, context, index_register, type);

            if (variable.get_scope() == ScopeLevel::LOCAL)
            {
                // Add index to base pointer
                stream << "add " << index_register << ", " << index_register << ", sp" << std::endl;
                // Get variable offset
                stream << context.store_instr(type) << " " << reg << ", " << variable.get_offset() << "(" << index_register << ")" << std::endl;
            }

            // If global scope, access global memory by targetting global label
            else if (variable.get_scope() == ScopeLevel::GLOBAL)
            {
                std::string global_memory_location = "global_" + GetIdentifier();
                std::string global_memory_register = context.get_register(Type::_INT);

                // Access global memory by targetting global label
                stream << "lui " << global_memory_register << ", " << "%hi(" << global_memory_location << ")" << std::endl;
                stream << "add " << global_memory_register << ", " << global_memory_register << ", " << index_register << std::endl;
                stream << context.store_instr(type) << " " << reg << ", %lo(" << global_memory_location << ")(" << global_memory_register << ")" << std::endl;

                context.deallocate_register(global_memory_register);
            }

            else
            {
                throw std::runtime_error("Assignment EmitRISC: Invalid scope in ArrayAccess");
            }

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

int Assignment::GetArraySize(Context &context) const
{
    const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(unary_expression_.get());

    if (array_declaration != nullptr)
    {

        if (array_declaration->GetArraySize(context) == -1)
        {
            return dynamic_cast<const ArrayInitialization *>(expression_.get())->GetArraySize();
        }
        return array_declaration->GetArraySize(context);
    }

    return 1;
}

bool Assignment::isArrayInitialization() const
{
    return dynamic_cast<const ArrayDeclaration *>(unary_expression_.get()) != nullptr;
}

void Assignment::InitializeGlobals(std::ostream &stream, Context &context, Global &global) const
{
    if (isArrayInitialization())
    {
        dynamic_cast<const ArrayInitialization *>(expression_.get())->InitializeGlobals(stream, context, global);
    }

    else
    {
        dynamic_cast<const Constant *>(expression_.get())->SaveValue(global);
    }
}


}
