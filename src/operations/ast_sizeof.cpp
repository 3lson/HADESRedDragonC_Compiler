#include "../../include/operations/ast_sizeof.hpp"

namespace ast{

Type SizeOf::GetType(Context &context) const
{
    (void)context;
    return Type::_INT;
}

void SizeOf::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const{
    (void)context;
    const TypeSpecifier *type_specifier = dynamic_cast<const TypeSpecifier *>(unary_expression_.get());
    const Operand *operand = dynamic_cast<const Operand *>(unary_expression_.get());

    Type type;

    if (type_specifier != nullptr){
        type = type_specifier->GetType();
    }
    else if (operand != nullptr){
        type = operand->GetType(context);
    }
    else{
        throw std::runtime_error("SizeOf::EmitRISC unary_expression is not a TypeSpecifier or Operand");
    }

    stream << "li " <<dest_reg << ", " << types_size.at(type) << std::endl;
}

void SizeOf::Print(std::ostream &stream) const{
    stream << "SizeOf(";
    unary_expression_->Print(stream);
    stream << ")";
}

}//namespace ast