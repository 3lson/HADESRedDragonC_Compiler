#include "../../include/pointers/ast_dereference.hpp"

namespace ast {

Type Dereference::GetType(Context& context) const
{
    Variable variable = context.get_variable(GetIdentifier());
    if (variable.get_dereference_num() == dereferenceCount()){
        return variable.get_type();
    }
    return Type::_INT;
}

bool Dereference::isPointer(Context &context) const{
    Variable variable = context.get_variable(GetIdentifier());
    if (variable.get_dereference_num() == dereferenceCount()){
        return true;
    }
    return false;
}


void Dereference::EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const
{
    Type type = GetType(context);

    std::string address_register = context.get_register(Type::_INT);
    StartingOffset(stream, context, address_register);

    DereferencePath(stream, context, address_register);
    stream << context.load_instr(type) << " " << dest_reg << ", 0(" << address_register << ")" << std::endl;

    context.deallocate_register(address_register);
}


void Dereference::Print(std::ostream& stream) const
{
    stream << "*";
    operand_->Print(stream);
}


std::string Dereference::GetIdentifier() const
{
    const Identifier* identifier = dynamic_cast<const Identifier*>(operand_.get());
    const ArrayIndexAccess* array_index_access = dynamic_cast<const ArrayIndexAccess*>(operand_.get());
    const Dereference* dereference = dynamic_cast<const Dereference*>(operand_.get());

    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    else if (array_index_access != nullptr)
    {
        return array_index_access->GetIdentifier();
    }
    else if (dereference != nullptr)
    {
        return dereference->GetIdentifier();
    }

    throw std::runtime_error("Dereference::GetIdentifier: Expected an identifier or array access");
}

int Dereference::dereferenceCount() const
{
    int count = 1;
    const Dereference *dereference = dynamic_cast<const Dereference *>(operand_.get());

    if (dereference != nullptr)
    {
        count += dereference->dereferenceCount();
    }

    return count;
}


void Dereference::DereferencePath(std::ostream &stream, Context &context, std::string address_reg) const
{
    std::string variable_identifier = GetIdentifier();

    const Dereference *dereference = dynamic_cast<const Dereference *>(operand_.get());

    if (dereference != nullptr)
    {
        dereference->DereferencePath(stream, context, address_reg);
    }

    stream << context.load_instr(Type::_INT) << " " << address_reg << ", 0(" << address_reg << ")" << std::endl;
}

void Dereference::StartingOffset(std::ostream &stream, Context &context, std::string address_reg) const
{
    std::string variable_identifier = GetIdentifier();
    Variable variable = context.get_variable(variable_identifier);
    ScopeLevel scope = variable.get_scope();
    Type type = GetType(context);

    if (scope == ScopeLevel::LOCAL)
    {
        stream << "addi " << address_reg << ", s0, " << variable.get_offset() << std::endl;
    }
    else if (scope == ScopeLevel::GLOBAL)
    {
        std::string global_label = "global_" + variable_identifier;
        stream << "lui " << address_reg << ", %hi(" << global_label << ")" << std::endl;
        stream << "addi " << address_reg << ", " << address_reg << ", %lo(" << global_label << ")" << std::endl;
    }

    const ArrayIndexAccess *array_index_access = dynamic_cast<const ArrayIndexAccess *>(operand_.get());
    if (array_index_access != nullptr)
    {
        std::string index_reg = context.get_register(Type::_INT);
        array_index_access->GetIndex(stream, context, address_reg, type);
        stream << "add " << address_reg << ", " << address_reg << ", " << index_reg << std::endl;
        context.deallocate_register(index_reg);
    }
}

bool Dereference::isPointerOp(Context &context) const
{
    return isPointer(context);
}

} // namespace ast