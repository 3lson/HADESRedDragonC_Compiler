#include "../../include/operations/ast_equality.hpp"

namespace ast {

std::string EqualityExpression::GetOperation(Type type) const {
    static const std::unordered_map<EqualityOp, std::unordered_map<Type, std::string>> opMap = {
        {EqualityOp::EQUAL, {
            {Type::_INT, "seqz"}, {Type::_UNSIGNED_INT, "seqz"}, {Type::_CHAR, "seqz"},
            {Type::_SHORT, "seqz"}, {Type::_LONG, "seqz"},
            {Type::_FLOAT, "feq.s"}, {Type::_DOUBLE, "feq.d"}
        }},
        {EqualityOp::NOT_EQUAL, {
            {Type::_INT, "snez"}, {Type::_UNSIGNED_INT, "snez"}, {Type::_CHAR, "snez"},
            {Type::_SHORT, "snez"}, {Type::_LONG, "snez"},
            {Type::_FLOAT, "feq.s"}, {Type::_DOUBLE, "feq.d"}  // feq.s needs inversion for !=
        }}
    };

    auto it = opMap.find(op_);
    if (it != opMap.end()) {
        auto typeIt = it->second.find(type);
        if (typeIt != it->second.end()) {
            return typeIt->second;
        }
    }

    throw std::runtime_error("Unsupported equality operation or type.");
}

void EqualityExpression::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.push_operation_type(type);
    bool is_float = (type == Type::_FLOAT || type == Type::_DOUBLE);
    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);
    context.add_register_to_set(left_register);

    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);

    std::string operation = GetOperation(type);

    if(is_float){
        stream << operation << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;

        if (op_ == EqualityOp::NOT_EQUAL){
            stream << "xori " << dest_reg << ", " <<dest_reg << ", 1" <<std::endl;
        }
    }
    else {
        stream << "xor " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << operation << " " << dest_reg << ", " << dest_reg << std::endl;
    }

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);
    context.remove_register_from_set(left_register);

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
