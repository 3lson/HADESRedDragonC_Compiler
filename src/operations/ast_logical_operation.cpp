#include "../../include/operations/ast_logical_operation.hpp"

namespace ast {

std::string LogicalExpression::GetOperation(Type type) const {
    static const std::unordered_map<LogicalOp, std::unordered_map<Type, std::string>> opMap = {
        {LogicalOp::LOGICAL_AND, {
            {Type::_INT, "and"}, {Type::_UNSIGNED_INT, "and"}, {Type::_CHAR, "and"},
            {Type::_SHORT, "and"}, {Type::_LONG, "and"}
        }},
        {LogicalOp::LOGICAL_OR, {
            {Type::_INT, "or"}, {Type::_UNSIGNED_INT, "or"}, {Type::_CHAR, "or"},
            {Type::_SHORT, "or"}, {Type::_LONG, "or"}
        }}
    };

    auto it = opMap.find(op_);
    if (it != opMap.end()) {
        auto typeIt = it->second.find(type);
        if (typeIt != it->second.end()) {
            return typeIt->second;
        }
    }

    throw std::runtime_error("Unsupported logical operation or type.");
}

void LogicalExpression::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const {
    Type type = std::max(context.get_operation_type(), GetType(context));

    context.set_operation_type(type);

    std::string left_register = context.get_register(type);
    std::string right_register = context.get_register(type);

    left_->EmitRISC(stream, context, left_register);
    right_->EmitRISC(stream, context, right_register);

    if (op_ == LogicalOp::LOGICAL_AND) {
        // Logical AND (&&): Short-circuit, only evaluate right if left is non-zero
        stream << "beqz " << left_register << ", false_label" << std::endl;
        stream << "snez " << dest_reg << ", " << right_register << std::endl;
        stream << "j end_label" << std::endl;
        stream << "false_label:" << std::endl;
        stream << "li " << dest_reg << ", 0" << std::endl;
    } else if (op_ == LogicalOp::LOGICAL_OR) {
        // Logical OR (||): Short-circuit, only evaluate right if left is zero
        stream << "snez " << dest_reg << ", " << left_register << std::endl;
        stream << "bnez " << dest_reg << ", end_label" << std::endl;
        stream << "snez " << dest_reg << ", " << right_register << std::endl;
    }

    stream << "end_label:" << std::endl;

    context.deallocate_register(right_register);
    context.deallocate_register(left_register);

    context.pop_operation_type();
}


// Print the logical expression as a string
void LogicalExpression::Print(std::ostream &stream) const {
    left_->Print(stream);
    switch (op_) {
        case LogicalOp::LOGICAL_AND: stream << " && "; break;
        case LogicalOp::LOGICAL_OR: stream << " || "; break;
    }
    right_->Print(stream);
}

// Get the type for the logical expression based on the operands' types
Type LogicalExpression::GetType(Context &context) const {
    if (!left_ || !right_) {
        throw std::runtime_error("Null pointer encountered in LogicalExpression operands.");
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

