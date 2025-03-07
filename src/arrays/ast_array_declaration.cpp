#include "../../include/arrays/ast_array_declaration.hpp"

namespace ast{
std::string ArrayDeclaration::GetIdentifier() const
{
    const Identifier *identifier = dynamic_cast<const Identifier *>(identifier_.get());
    if (identifier != nullptr)
    {
        return identifier->GetIdentifier();
    }
    throw std::runtime_error("ArrayDeclaration::GetIdentifier - not an identifier");
}

int ArrayDeclaration::GetArraySize() const
{
    if (constant_expression_ == nullptr)
    {
        return -1;
    }
    const IntConstant *constant_expression = dynamic_cast<const IntConstant *>(constant_expression_.get());
    if (constant_expression != nullptr)
    {
        return constant_expression->GetValue();
    }
    throw std::runtime_error("ArrayDeclaration::GetArraySize - array is null");
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
}
