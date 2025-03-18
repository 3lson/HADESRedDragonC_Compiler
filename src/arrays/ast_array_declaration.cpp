#include "../../include/arrays/ast_array_declaration.hpp"

namespace ast{
std::string ArrayDeclaration::GetId() const
{
    const Identifier *identifier = dynamic_cast<const Identifier *>(identifier_.get());
    const Declarator *declarator = dynamic_cast<const Declarator *>(identifier_.get());
    if (identifier != nullptr)
    {
        return identifier->GetId();
    }
    else if (declarator != nullptr)
    {
        return declarator->GetId();
    }
    throw std::runtime_error("ArrayDeclaration::GetId - not an identifier");
}

int ArrayDeclaration::GetArraySize(Context &context) const
{
    if (constant_expression_ == nullptr)
    {
        return -1;
    }
    const IntConstant *int_const = dynamic_cast<const IntConstant *>(constant_expression_.get());
    const Identifier *enumerator = dynamic_cast<const Identifier *>(constant_expression_.get());
    if (int_const != nullptr)
    {
        return int_const->GetValue();
    }
    if (enumerator != nullptr)
    {
        return enumerator->GetValue(context);
    }
    throw std::runtime_error("ArrayDeclaration::GetArraySize - array is null and neither is a enumerator");
}

void ArrayDeclaration::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)stream;
    (void)context;
    (void)dest_reg;
}

void ArrayDeclaration::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    stream << "[";
    if (constant_expression_ != nullptr)
    {
        constant_expression_->Print(stream);
    }
    stream << "]";
}

bool ArrayDeclaration::isPointer() const
{
    return dynamic_cast<const PointerDeclaration *>(identifier_.get()) != nullptr;
}

std::vector<Parameter> ArrayDeclaration::GetParameters(Context &context) const
{
    return dynamic_cast<const Declarator *>(identifier_.get())->GetParameters(context);
}

int ArrayDeclaration::GetOffset() const
{
    return dynamic_cast<const Declarator *>(identifier_.get())->GetOffset();
}

void ArrayDeclaration::StoreParameters(std::ostream &stream, Context &context, std::string dest_reg) const
{
    return dynamic_cast<const Declarator *>(identifier_.get())->StoreParameters(stream, context, dest_reg);
}

int ArrayDeclaration::GetDereference() const
{
    const Declarator *declarator = dynamic_cast<const Declarator *>(identifier_.get());
    if (declarator)
    {
        return declarator->GetDereference();
    }

    return 0;
}


}
