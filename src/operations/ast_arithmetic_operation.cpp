#include "../../include/operations/ast_arithmetic_operation.hpp"

namespace ast {

std::string ArithExpression::GetOperation(Type type) const {
    static const std::unordered_map<ArithOp, std::unordered_map<Type, std::string>> opMap = {
        {ArithOp::ADD, {
            {Type::_INT, "add"}, {Type::_UNSIGNED_INT, "add"}, {Type::_CHAR, "add"},
            {Type::_SHORT, "add"}, {Type::_LONG, "add"},
            {Type::_FLOAT, "fadd.s"}, {Type::_DOUBLE, "fadd.d"}
        }},
        {ArithOp::SUB, {
            {Type::_INT, "sub"}, {Type::_UNSIGNED_INT, "sub"}, {Type::_CHAR, "sub"},
            {Type::_SHORT, "sub"}, {Type::_LONG, "sub"},
            {Type::_FLOAT, "fsub.s"}, {Type::_DOUBLE, "fsub.d"}
        }},
        {ArithOp::MUL, {
            {Type::_INT, "mul"}, {Type::_UNSIGNED_INT, "mul"}, {Type::_CHAR, "mul"},
            {Type::_SHORT, "mul"}, {Type::_LONG, "mul"},
            {Type::_FLOAT, "fmul.s"}, {Type::_DOUBLE, "fmul.d"}
        }},
        {ArithOp::DIV, {
            {Type::_INT, "div"}, {Type::_UNSIGNED_INT, "div"}, {Type::_CHAR, "div"},
            {Type::_SHORT, "div"}, {Type::_LONG, "div"},
            {Type::_FLOAT, "fdiv.s"}, {Type::_DOUBLE, "fdiv.d"}
        }},
        {ArithOp::MOD, {
            {Type::_INT, "rem"}, {Type::_UNSIGNED_INT, "rem"}, {Type::_CHAR, "rem"},
            {Type::_SHORT, "rem"}, {Type::_LONG, "rem"},
            {Type::_FLOAT, "frem.s"}, {Type::_DOUBLE, "frem.d"}
        }}
    };

    auto it = opMap.find(op_);
    if (it != opMap.end()) {
        auto typeIt = it->second.find(type);
        if (typeIt != it->second.end()) {
            return typeIt->second;
        }
    }

    throw std::runtime_error("Unsupported arithmetic operation or type.");
}

void ArithExpression::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.push_operation_type(type);

    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);
    context.add_register_to_set(left_register);

    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);
    stream << GetOperation(type) << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);
    context.remove_register_from_set(left_register);

    context.pop_operation_type();
}

void ArithExpression::Print(std::ostream &stream) const
{
    left_->Print(stream);
    switch(op_){
        case ArithOp::ADD: stream << " + "; break;
        case ArithOp::SUB: stream << " - "; break;
        case ArithOp::MUL: stream << " * "; break;
        case ArithOp::DIV: stream << " / "; break;
        case ArithOp::MOD: stream << " % "; break;
    }
    right_->Print(stream);
}

Type ArithExpression::GetType(Context &context) const
{
    if (!left_ || !right_) {
        throw std::runtime_error("Null pointer encountered in ArithExpression operands.");
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


}
