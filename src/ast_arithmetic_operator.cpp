#include "ast_arithmetic_operator.hpp"

namespace ast{

void ArithExpression::EmitRISC(std::ostream& stream, Context& context) const {
    left_->EmitRISC(stream, context);  // Compute left operand
    stream << "mv t1, a0" << std::endl; // Move left result to t1

    right_->EmitRISC(stream, context); // Compute right operand
    stream << "mv t2, a0" << std::endl; // Move right result to t2

    switch (op_) {
        case ArithOp::ADD:
            stream << "add a0, t1, t2" << std::endl;
            break;
        case ArithOp::SUB:
            stream << "sub a0, t1, t2" << std::endl;
            break;
        case ArithOp::MUL:
            stream << "mul a0, t1, t2" << std::endl;
            break;
        case ArithOp::DIV:
            stream << "div a0, t1, t2" << std::endl;
            break;
        case ArithOp::MODULO:
            stream << "rem a0, t1, t2" << std::endl;
            break;
        case ArithOp::BITWISE_AND:
            stream << "and a0, t1, t2" << std::endl;
            break;
        case ArithOp::BITWISE_OR:
            stream << "or a0, t1, t2" << std::endl;
            break;
        case ArithOp::BITWISE_XOR:
            stream << "xor a0, t1, t2" << std::endl;
            break;
        case ArithOp::EQUAL:
            stream << "xor t3, t1, t2" << std::endl;
            stream << "seqz a0, t3" << std::endl;
            break;
        case ArithOp::NOT_EQUAL:
            stream << "xor t3, t1, t2" << std::endl; // XOR to check inequality
            stream << "snez a0, t3" << std::endl; // Set a0 to 1 if not equal, else 0
            break;
        case ArithOp::LESS_THAN:
            stream << "slt a0, t1, t2" << std::endl;
            break;
        case ArithOp::GREATER_THAN:
            stream << "sgt a0, t1, t2" << std::endl;
            break;
        case ArithOp::LESS_THAN_OR_EQUAL:
            stream << "slt t3, t2, t1" << std::endl; // t3 = (t2 < t1) -> opposite of t1 <= t2
            stream << "seqz a0, t3" << std::endl;   // a0 = !(t3)
            break;
        case ArithOp::GREATER_THAN_OR_EQUAL:
            stream << "slt t3, t1, t2" << std::endl; // t3 = (t1 < t2)
            stream << "seqz a0, t3" << std::endl;   // a0 = !(t3)
            break;
        case ArithOp::LOGICAL_AND:
            stream << "snez t1, t1" << std::endl;
            stream << "snez t2, t2" << std::endl;
            stream << "and a0, t1, t2" << std::endl;
            break;
        case ArithOp::LOGICAL_OR:
            stream << "or a0, t1, t2" << std::endl;
            stream << "snez a0, a0" << std::endl;
            break;
        case ArithOp::LEFT_SHIFT:
            stream << "sll a0, t1, t2" << std::endl;     // Shift Left Logical
            break;
        case ArithOp::RIGHT_SHIFT:
            stream << "srl a0, t1, t2" << std::endl;     // Shift Right Logical
            break;
    }
}

void ArithExpression::Print(std::ostream& stream) const {
    stream << "(";
    left_->Print(stream);
    switch (op_) {
        case ArithOp::ADD: stream << " + "; break;
        case ArithOp::SUB: stream << " - "; break;
        case ArithOp::MUL: stream << " * "; break;
        case ArithOp::DIV: stream << " / "; break;
        case ArithOp::MODULO: stream << " % "; break;
        case ArithOp::BITWISE_AND: stream << " & "; break;
        case ArithOp::BITWISE_OR: stream << " | "; break;
        case ArithOp::BITWISE_XOR: stream << " ^ "; break;
        case ArithOp::EQUAL: stream << " == "; break;
        case ArithOp::NOT_EQUAL: stream << " != "; break;
        case ArithOp::LESS_THAN: stream << " < "; break;
        case ArithOp::GREATER_THAN: stream << " > "; break;
        case ArithOp::LESS_THAN_OR_EQUAL: stream << " <= "; break;
        case ArithOp::GREATER_THAN_OR_EQUAL: stream << " >= "; break;
        case ArithOp::LOGICAL_AND: stream << " && "; break;
        case ArithOp::LOGICAL_OR: stream << " || "; break;
        case ArithOp::LEFT_SHIFT: stream << " << "; break;
        case ArithOp::RIGHT_SHIFT: stream << " >> "; break;
    }
    right_->Print(stream);
    stream << ")";
}



}//namespace ast
