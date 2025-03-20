#include "../../include/operations/ast_sizeof.hpp"

namespace ast{

Type SizeOf::GetType(Context &context) const
{
    (void)context;
    return Type::_INT;
}

void SizeOf::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const{
    (void)context;
    std::cout << "Type_id of unary_expression_: " << typeid(unary_expression_.get()).name() << std::endl;
    const Specifier *type_specifier = dynamic_cast<const Specifier *>(unary_expression_.get());
    const Operand *operand = dynamic_cast<const Operand *>(unary_expression_.get());
    Type type;
    int size =0;

    if (type_specifier != nullptr){
        type = type_specifier->GetType();
        if (pointer_ > 0){
            type = Type::_INT;
        }
        size = types_size.at(type);
    }
    else if (operand != nullptr){
        type = operand->isPointerOp(context) ? Type::_INT : operand->GetType(context);
        std::cout << "Type_id for operand: " <<typeid(operand).name() << std::endl;

        if (const Identifier* id = dynamic_cast<const Identifier*>(operand)) {
            std::cout << "Identifier found: " << id->GetId() << std::endl;

            // If it's an Identifier, use its ID (for example to look up the struct size)
            size = context.get_struct_size(id->GetId());
        } else {
            std::cout << "Operand id is not available" << std::endl;
        }

        if (type == Type::_STRUCT){
            const StructAccess* struct_access = dynamic_cast<const StructAccess *>(operand);
            if(struct_access){
                std::cout <<"Type_id for identifier: " << typeid(struct_access).name() << std::endl;
            }
        }
        else{
            size = types_size.at(type);
        }

    } else {
        throw std::runtime_error("SizeOf::EmitRISC - Unary expression is not a TypeSpecifier or Operand.");
    }

    if (constant_expression_)
    {
        size *= dynamic_cast<const IntConstant *>(constant_expression_.get())->GetValue();
    }

    stream << "li " <<dest_reg << ", " << size << std::endl;
}

void SizeOf::Print(std::ostream &stream) const{
    stream << "SizeOf(";
    unary_expression_->Print(stream);
    stream << ")";
}

bool SizeOf::isPointerOp(Context &context) const
{
    (void)context;
    return false;
}


}//namespace ast