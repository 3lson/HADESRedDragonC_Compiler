#include "../../include/operations/ast_relational_operation.hpp"

namespace ast {

std::string RelationExpression::GetOperation(Type type) const {
    static const std::unordered_map<RelationOp, std::unordered_map<Type, std::string>> opMap = {
        {RelationOp::LESS_THAN, {
            {Type::_INT, "slt"}, {Type::_UNSIGNED_INT, "sltu"}, {Type::_CHAR, "slt"},
            {Type::_SHORT, "slt"},
            {Type::_FLOAT, "flt.s"}, {Type::_DOUBLE, "flt.d"}
        }},
        {RelationOp::GREATER_THAN, {
            {Type::_INT, "sgt"}, {Type::_UNSIGNED_INT, "sgtu"}, {Type::_CHAR, "sgt"},
            {Type::_SHORT, "sgt"},
            {Type::_FLOAT, "fgt.s"}, {Type::_DOUBLE, "fgt.d"}
        }},
        {RelationOp::LESS_THAN_OR_EQUAL, {
            {Type::_INT, "sgt"}, {Type::_UNSIGNED_INT, "sgtu"}, {Type::_CHAR, "sgt"},
            {Type::_SHORT, "sgt"},
            {Type::_FLOAT, "fgt.s"}, {Type::_DOUBLE, "fgt.d"}
        }},
        {RelationOp::GREATER_THAN_OR_EQUAL, {
            {Type::_INT, "slt"}, {Type::_UNSIGNED_INT, "sltu"}, {Type::_CHAR, "slt"},
            {Type::_SHORT, "slt"},
            {Type::_FLOAT, "flt.s"}, {Type::_DOUBLE, "flt.d"}
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

void RelationExpression::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    //Type type = std::max(context.get_operation_type(), GetType(context));

    Type right_type = dynamic_cast<const Operand *>(right_.get())->GetType(context);
    Type left_type = dynamic_cast<const Operand *>(left_.get())->GetType(context);
    Type type = std::max(right_type, left_type);
    type = isPointerOp(context) ? Type::_INT : type;
    context.push_operation_type(type);

    std::string left_register = context.get_register(type);
    left_->EmitRISC(stream, context, left_register);
    ShiftPointerOp(stream, context, left_register, left_);
    context.add_register_to_set(left_register);
    std::string right_register = context.get_register(type);
    right_->EmitRISC(stream, context, right_register);
    ShiftPointerOp(stream, context, right_register, right_);

    // Handle LESS_THAN or GREATER_THAN and others normally
    if (op_ == RelationOp::LESS_THAN) {
        stream << GetOperation(type) << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
    }
    else if (op_ == RelationOp::GREATER_THAN) {
        stream << GetOperation(type) << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
    }
    // Handle LESS_THAN_OR_EQUAL: Invert the result of LESS_THAN
    else if (op_ == RelationOp::LESS_THAN_OR_EQUAL) {
        stream << GetOperation(type) << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "xori " << dest_reg << ", " << dest_reg << ", 1" << std::endl; // Inverts the result
    }
    // Handle GREATER_THAN_OR_EQUAL: Invert the result of GREATER_THAN
    else if (op_ == RelationOp::GREATER_THAN_OR_EQUAL) {
        stream << GetOperation(type) << " " << dest_reg << ", " << left_register << ", " << right_register << std::endl;
        stream << "xori " << dest_reg << ", " << dest_reg << ", 1" << std::endl; // Inverts the result
    }

    // Clean up: Deallocate registers and reset operation type
    context.deallocate_register(right_register);
    context.deallocate_register(left_register);
    context.remove_register_from_set(left_register);
    context.pop_operation_type();
}


void RelationExpression::Print(std::ostream &stream) const
{
    left_->Print(stream);
    switch(op_){
        case RelationOp::LESS_THAN: stream << " < "; break;
        case RelationOp::GREATER_THAN: stream << " > "; break;
        case RelationOp::LESS_THAN_OR_EQUAL: stream << " <= "; break;
        case RelationOp::GREATER_THAN_OR_EQUAL: stream << " >= "; break;
    }
    right_->Print(stream);
}

Type RelationExpression::GetType(Context &context) const
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

bool RelationExpression::isPointerOp(Context &context) const
{
    // Attempt to cast left_ and right_ to Operand
    const Operand *left_operand = dynamic_cast<const Operand *>(left_.get());
    const Operand *right_operand = dynamic_cast<const Operand *>(right_.get());

    // Return true if either operand is a pointer
    return left_operand->isPointerOp(context) || right_operand->isPointerOp(context);
}

void RelationExpression::ShiftPointerOp(std::ostream &stream, Context &context, std::string dest_reg, const NodePtr& node) const
{
    if (isPointerOp(context))
    {
        const Operand* operand = dynamic_cast<const Operand*>(node.get());
        if (operand && !operand->isPointerOp(context))
        {
            stream << "slli " << dest_reg << ", " << dest_reg << ", " << types_mem_shift.at(GetType(context)) << std::endl;
        }
    }
}


}
