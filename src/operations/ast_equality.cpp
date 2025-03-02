#include "../../include/operations/ast_equality.hpp"

namespace ast {

    void EqualityExpression::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);
    std::string right_register = context.get_register(type);

    left_->EmitRISC(stream, context, left_register);
    right_->EmitRISC(stream, context, right_register);

    if (op_ == EqualityOp::EQUAL) {
        stream << "xor " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "seqz " << dest_reg << ", " << dest_reg << std::endl;
    }
    else if (op_ == EqualityOp::NOT_EQUAL) {
        stream << "xor " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "snez " << dest_reg << ", " << dest_reg << std::endl;
    }
    else {
        throw std::runtime_error("Unknown equality operation.");
    }

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);

    context.pop_operation_type();
}

void EqualityExpression::Print(std::ostream &stream) const
{
    left_->Print(stream);
    switch(op_){
        case EqualityOp::EQUAL: stream << " == "; break;
        case EqualityOp::NOT_EQUAL: stream << " != "; break;
    }
    right_->Print(stream);
}

Type EqualityExpression::GetType(Context &context) const
{
    if (!left_ || !right_) {
        throw std::runtime_error("Null pointer encountered in EqualityExpression operands.");
    }

    const Operand* leftOperand = dynamic_cast<const Operand*>(left_.get());
    const Operand* rightOperand = dynamic_cast<const Operand*>(right_.get());

    if (!leftOperand) {
        throw std::runtime_error("Invalid left operand type: " + std::string(typeid(*left_).name()));
    }
    if (!rightOperand) {
        throw std::runtime_error("Invalid right operand type: " + std::string(typeid(*right_).name()));
    }

    Type leftType = leftOperand->GetType(context);
    Type rightType = rightOperand->GetType(context);

    return std::max(leftType, rightType);
}

} // namespace ast
