#include "ast_arithmetic_operator.hpp"

namespace ast{

void ArithExpression::EmitRISC(std::ostream& stream, Context& context) const {
    context.SetarithFlag();

    context.ResetequatingvarFlag(); //turns this off during assignment to prevent different behaviour for identifier and const

    if(context.GetretFlag() == true){
        context.ResetretFlag();
        context.SetarithconstinitFlag();

        left_->EmitRISC(stream,context);
        right_->EmitRISC(stream,context);

        context.ResetarithconstinitFlag();
        context.SetretFlag();

    }
    else if(!context.GetsecondcallFlag()){
        context.SetarithconstinitFlag();

        left_->EmitRISC(stream,context);
        right_->EmitRISC(stream,context);

        context.ResetarithconstinitFlag();
    }

    std::string tempreg;

    for(int i = 0; i < 7; i++){
        if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
            tempreg = std::string("t") + std::to_string(i);
            break;
        }
    }

    context.MapRegister("   ",tempreg);

    if(context.GetretFlag() == true){
        std::string retreg;

        retreg = "a0";

        switch (op_) {
            case ArithOp::ADD:
                stream << "add " << retreg << ", ";
                break;
            case ArithOp::SUB:
                stream << "sub " << retreg << ", ";
                break;
            case ArithOp::MUL:
                stream << "mul " << retreg << ", ";
                break;
            case ArithOp::DIV:
                stream << "div " << retreg << ", ";
                break;
            case ArithOp::MODULO:
                stream << "rem " << retreg <<", ";
                break;
            case ArithOp::BITWISE_AND:
                stream << "and " << retreg << ", ";
                break;
            case ArithOp::BITWISE_OR:
                stream << "or "<< retreg << ", ";
                break;
            case ArithOp::BITWISE_XOR:
                stream << "xor " << retreg << ",";
                break;
            case ArithOp::EQUAL:
                stream << "xor "<< tempreg << ", ";
                break;
            case ArithOp::NOT_EQUAL:
                stream << "xor " << tempreg << ", "; // XOR to check inequality
                break;
            case ArithOp::LESS_THAN:
                stream << "slt " << retreg << ", ";
                break;
            case ArithOp::GREATER_THAN:
                stream << "sgt " << retreg << ", ";
                break;
            case ArithOp::LESS_THAN_OR_EQUAL:
                stream << "sgt " << tempreg << ", "; // t3 = (t2 < t1) -> opposite of t1 <= t2
                break;
            case ArithOp::GREATER_THAN_OR_EQUAL:
                stream << "slt " << tempreg << ", " << std::endl; // t3 = (t1 < t2)
                break;
            case ArithOp::LOGICAL_AND:
                stream << "snez ";
                left_->EmitRISC(stream,context);
                stream << ", ";
                left_->EmitRISC(stream,context);
                stream <<std::endl;
                stream << "snez ";
                right_->EmitRISC(stream,context);
                stream << ", ";
                right_->EmitRISC(stream,context);
                stream << std::endl;
                stream << "and "<< retreg <<", ";
                break;
            case ArithOp::LOGICAL_OR:
                stream << "or "<< retreg <<", ";
                break;
            case ArithOp::LEFT_SHIFT:
                stream << "sll "<< retreg <<", ";   // Shift Left Logical
                break;
            case ArithOp::RIGHT_SHIFT:
                stream << "srl "<< retreg <<", ";    // Shift Right Logical
                break;
        }

        switch(op_){
            case ArithOp::ADD:
            case ArithOp::SUB:
            case ArithOp::MUL:
            case ArithOp::DIV:
            case ArithOp::MODULO:
            case ArithOp::BITWISE_AND:
            case ArithOp::BITWISE_OR:
            case ArithOp::BITWISE_XOR:
            case ArithOp::EQUAL:
            case ArithOp::NOT_EQUAL:
            case ArithOp::LESS_THAN_OR_EQUAL:
            case ArithOp::GREATER_THAN_OR_EQUAL:
            case ArithOp::LESS_THAN:
            case ArithOp::GREATER_THAN:
            case ArithOp::LOGICAL_AND:
            case ArithOp::LOGICAL_OR:
                left_->EmitRISC(stream, context);  // Compute left operand
                stream << ", ";
                right_->EmitRISC(stream, context); // Computer right operand
                break;
            case ArithOp::RIGHT_SHIFT:
            case ArithOp::LEFT_SHIFT:
                left_->EmitRISC(stream, context);  // Compute left operand
                break;


        }


        switch (op_) {
            case ArithOp::ADD:
                stream << std::endl;
                break;
            case ArithOp::SUB:
                stream << std::endl;
                break;
            case ArithOp::MUL:
                stream << std::endl;
                break;
            case ArithOp::DIV:
                stream << std::endl;
                break;
            case ArithOp::MODULO:
                stream << std::endl;
                break;
            case ArithOp::BITWISE_AND:
                stream << std::endl;
                break;
            case ArithOp::BITWISE_OR:
                stream << std::endl;
                break;
            case ArithOp::BITWISE_XOR:
                stream << std::endl;
                break;
            case ArithOp::LOGICAL_AND:
                stream << std::endl;
                break;
            case ArithOp::LEFT_SHIFT:
                stream << std::endl;
                break;
            case ArithOp::RIGHT_SHIFT:
                stream << std::endl;
                break;
            case ArithOp::LESS_THAN:
                stream << std::endl;
                break;
            case ArithOp::GREATER_THAN:
                stream << std::endl;
                break;
            case ArithOp::EQUAL:
                stream << std::endl;
                stream << "seqz " << retreg << ", " << tempreg <<  std::endl;
                break;
            case ArithOp::NOT_EQUAL:
                stream << "snez "<< retreg << ", " << tempreg << std::endl; // Set a0 to 1 if not equal, else 0
                break;
            case ArithOp::LESS_THAN_OR_EQUAL:
                stream << std::endl;
                stream << "seqz " << retreg << ", " << tempreg << std::endl;   // a0 = !(t3)
                break;
            case ArithOp::GREATER_THAN_OR_EQUAL:
                stream << "seqz " << retreg << ", " << tempreg << std::endl;   // a0 = !(t3)
                break;
            case ArithOp::LOGICAL_OR:
                stream << std::endl;
                stream << "snez "<< retreg <<", "<< retreg << std::endl;
                break;
        }

    }
    else if(context.GetassignFlag()){

        if(context.GetRegister("arithassign") != ""){
            stream << context.GetRegister("arithassign");
            context.FreeRegister("arithassign");
        }
        else{

            context.SetexpressionassignFlag();

            std::string tempreg2;

            for(int i = 0; i < 7; i++){
                if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                    tempreg2 = std::string("t") + std::to_string(i);
                    break;
                }
            }

            context.MapRegister("arithassign",tempreg2);

            switch (op_) {
                case ArithOp::ADD:
                    stream << "add " << tempreg2 << ", ";
                    break;
                case ArithOp::SUB:
                    stream << "sub " << tempreg2 << ", ";
                    break;
                case ArithOp::MUL:
                    stream << "mul " << tempreg2 << ", ";
                    break;
                case ArithOp::DIV:
                    stream << "div " << tempreg2 << ", ";
                    break;
                case ArithOp::MODULO:
                    stream << "rem " << tempreg2 <<", ";
                    break;
                case ArithOp::BITWISE_AND:
                    stream << "and " << tempreg2 << ", ";
                    break;
                case ArithOp::BITWISE_OR:
                    stream << "or "<< tempreg2 << ", ";
                    break;
                case ArithOp::BITWISE_XOR:
                    stream << "xor " << tempreg2 << ",";
                    break;
                case ArithOp::EQUAL:
                    stream << "xor "<< tempreg << ", ";
                    break;
                case ArithOp::NOT_EQUAL:
                    stream << "xor " << tempreg << ", "; // XOR to check inequality
                    break;
                case ArithOp::LESS_THAN:
                    stream << "slt " << tempreg2 << ", ";
                    break;
                case ArithOp::GREATER_THAN:
                    stream << "sgt " << tempreg2 << ", ";
                    break;
                case ArithOp::LESS_THAN_OR_EQUAL:
                    stream << "sgt " << tempreg << ", "; // t3 = (t2 < t1) -> opposite of t1 <= t2
                    break;
                case ArithOp::GREATER_THAN_OR_EQUAL:
                    stream << "slt " << tempreg << ", " << std::endl; // t3 = (t1 < t2)
                    break;
                case ArithOp::LOGICAL_AND:
                    stream << "snez ";
                    left_->EmitRISC(stream,context);
                    stream << ", ";
                    left_->EmitRISC(stream,context);
                    stream << std::endl;
                    stream << "snez ";
                    right_->EmitRISC(stream,context);
                    stream << ", ";
                    right_->EmitRISC(stream,context);
                    stream << std::endl;
                    stream << "and "<< tempreg2 <<", ";
                    break;
                case ArithOp::LOGICAL_OR:
                    stream << "or "<< tempreg2 << ", ";
                    break;
                case ArithOp::LEFT_SHIFT:
                    stream << "sll "<< tempreg2 <<", ";   // Shift Left Logical
                    break;
                case ArithOp::RIGHT_SHIFT:
                    stream << "srl "<< tempreg2 <<", ";    // Shift Right Logical
                    break;
            }

            switch(op_){
                case ArithOp::ADD:
                case ArithOp::SUB:
                case ArithOp::MUL:
                case ArithOp::DIV:
                case ArithOp::MODULO:
                case ArithOp::BITWISE_AND:
                case ArithOp::BITWISE_OR:
                case ArithOp::BITWISE_XOR:
                case ArithOp::EQUAL:
                case ArithOp::NOT_EQUAL:
                case ArithOp::LESS_THAN_OR_EQUAL:
                case ArithOp::GREATER_THAN_OR_EQUAL:
                case ArithOp::LESS_THAN:
                case ArithOp::GREATER_THAN:
                case ArithOp::LOGICAL_AND:
                case ArithOp::LOGICAL_OR:
                    left_->EmitRISC(stream, context);  // Compute left operand
                    stream << ", ";
                    right_->EmitRISC(stream, context); // Computer right operand
                    break;
                case ArithOp::RIGHT_SHIFT:
                case ArithOp::LEFT_SHIFT:
                    left_->EmitRISC(stream, context);  // Compute left operand
                    break;


            }


            switch (op_) {
                case ArithOp::ADD:
                    stream << std::endl;
                    break;
                case ArithOp::SUB:
                    stream << std::endl;
                    break;
                case ArithOp::MUL:
                    stream << std::endl;
                    break;
                case ArithOp::DIV:
                    stream << std::endl;
                    break;
                case ArithOp::MODULO:
                    stream << std::endl;
                    break;
                case ArithOp::BITWISE_AND:
                    stream << std::endl;
                    break;
                case ArithOp::BITWISE_OR:
                    stream << std::endl;
                    break;
                case ArithOp::BITWISE_XOR:
                    stream << std::endl;
                    break;
                case ArithOp::LOGICAL_AND:
                    stream << std::endl;
                    break;
                case ArithOp::LEFT_SHIFT:
                    stream << std::endl;
                    break;
                case ArithOp::RIGHT_SHIFT:
                    stream << std::endl;
                    break;
                case ArithOp::LESS_THAN:
                    stream << std::endl;
                    break;
                case ArithOp::GREATER_THAN:
                    stream << std::endl;
                    break;
                case ArithOp::EQUAL:
                    stream << std::endl;
                    stream << "seqz " << tempreg2 << ", " << tempreg <<  std::endl;
                    break;
                case ArithOp::NOT_EQUAL:
                    stream << "snez "<< tempreg2 << ", " << tempreg << std::endl; // Set a0 to 1 if not equal, else 0
                    break;
                case ArithOp::LESS_THAN_OR_EQUAL:
                    stream << std::endl;
                    stream << "seqz " << tempreg2 << ", " << tempreg << std::endl;   // a0 = !(t3)
                    break;
                case ArithOp::GREATER_THAN_OR_EQUAL:
                    stream << "seqz " << tempreg2 << ", " << tempreg << std::endl;   // a0 = !(t3)
                    break;
                case ArithOp::LOGICAL_OR:
                    stream << std::endl;
                    stream << "snez "<< tempreg2 <<", "<< tempreg2 << std::endl;
                    break;
            }

        }


    }

    context.ResetarithFlag();
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
