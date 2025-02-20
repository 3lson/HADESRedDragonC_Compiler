#include "ast_unary.hpp"

namespace ast {

void UnaryExpression::EmitRISC(std::ostream& stream, Context& context) const {
    operand_->EmitRISC(stream, context);  // Compute operand
    stream << "mv t1, a0" << std::endl;   // Move oxperand result to t1

    switch (op_) {
        case UnaryOp::PLUS:
            // Unary plus does nothing to the operand, just return it
            stream << "mv a0, t1" << std::endl; // Copy operand
            break;
        case UnaryOp::MINUS:
            stream << "neg a0, t1" << std::endl; // Negate the value (i.e., -operand)
            break;
        case UnaryOp::BITWISE_NOT:
            stream << "not a0, t1" << std::endl; // Bitwise NOT operation (~)
            break;
        case UnaryOp::LOGICAL_NOT:
            stream << "seqz a0, t1" << std::endl; // Logical NOT (if operand is zero, a0 = 1, else a0 = 0)
            break;
        case UnaryOp::INCREMENT:
            stream << "addi a0, t1, 1" << std::endl; // Increment operand by 1
            break;
        case UnaryOp::DECREMENT:
            stream << "addi a0, t1, -1" << std::endl; // Decrement operand by 1
            break;
    }
}

void UnaryExpression::Print(std::ostream& stream) const {
    stream << "(";
    switch (op_) {
        case UnaryOp::PLUS: stream << "+"; break;
        case UnaryOp::MINUS: stream << "-"; break;
        case UnaryOp::BITWISE_NOT: stream << "~"; break;
        case UnaryOp::LOGICAL_NOT: stream << "!"; break;
        case UnaryOp::INCREMENT: stream << "++"; break;
        case UnaryOp::DECREMENT: stream << "--"; break;
    }
    operand_->Print(stream);
    stream << ")";
}

} // namespace ast
