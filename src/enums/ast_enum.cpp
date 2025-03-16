#include "../../include/enums/ast_enum.hpp"

namespace ast{
std::string Enumerator::GetLabel() const
{
    return label_;
}

int Enumerator::DefineEnumerator(Context &context, int value) const
{

    if (constant_expression_)
    {
        value = GetValue(context);
    }

    context.define_enum_label(label_, value);
    return value + 1;
}

void Enumerator::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)context;
    (void)dest_reg;
    (void)stream;
    throw std::runtime_error("Enumerator::EmitRISC not implemented");
}

void Enumerator::Print(std::ostream &stream) const
{
    stream << label_;

    if (constant_expression_)
    {
        stream << " = ";
        constant_expression_->Print(stream);
    }

    stream << "," << std::endl;
}

int Enumerator::GetValue(Context &context) const
{
    const Identifier *enumerator = dynamic_cast<const Identifier *>(constant_expression_.get());
    const IntConstant *int_constant = dynamic_cast<const IntConstant *>(constant_expression_.get());

    if (enumerator != nullptr)
    {
        return enumerator->GetValue(context);
    }

    else if (int_constant != nullptr)
    {
        return int_constant->GetValue();
    }

    throw std::runtime_error("Enumerator::GetValue - constant_expression not recognised");
}
}//namespace ast
