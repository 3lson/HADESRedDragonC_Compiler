#include "../../include/operations/ast_arithmetic_operator.hpp"

namespace ast{

void ArithExpression::SetUniqueVarValue(Context& context,const std::string& basename) const{
    var_ = context.getUniqueName(basename);
}

void ArithExpression::OperationExecutor(std::ostream& stream, Context& context, const std::string& retreg, const std::string& tempreg) const{
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
            context.Setarithoperandreturn();
            left_->EmitRISC(stream,context);
            stream << ", ";
            left_->EmitRISC(stream,context);
            stream <<std::endl;
            stream << "snez ";
            right_->EmitRISC(stream,context);
            stream << ", ";
            right_->EmitRISC(stream,context);
            context.Resetarithoperandreturn();
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
            context.Setarithoperandreturn();
            left_->EmitRISC(stream, context);  // Compute left operand
            stream << ", ";
            right_->EmitRISC(stream, context); // Computer right operand
            context.Resetarithoperandreturn();
            break;
        case ArithOp::RIGHT_SHIFT:
        case ArithOp::LEFT_SHIFT:
            context.Setarithoperandreturn();
            left_->EmitRISC(stream, context);  // Compute left operand
            context.Resetarithoperandreturn();
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

void ArithExpression::EmitRISC(std::ostream& stream, Context& context) const {

    std::string scopelevel = std::to_string(context.GetscopeLevel());

    if(context.GetarithFlag()){
        context.SetarithoperandFlag();
         //add within if statement
    }

    context.SetarithFlag();
    context.ResetequatingvarFlag(); //turns this off during assignment to prevent different behaviour for identifier and const

    if(!context.Getarithoperandreturn()){
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

    }

    if((context.GetretFlag()) || (context.GetassignFlag()) || (context.GetwhileFlag())){ //indicates that this node is the top level arith node
        context.ResetarithoperandFlag();
    }

    //make sure to treat assign and while flags the same


    std::string tempreg = context.GetFreeRegister("t",0,6);

    context.MapRegister(" ",tempreg);


    if(context.GetarithoperandFlag()){

        bool Retwashigh = false;
        if(context.GetretFlag()){
            context.ResetretFlag();
            Retwashigh = true;
        }


        if(var_ != ""){
            stream << context.GetRegister(var_);
            context.FreeRegister(var_);
        }
        else{

            std::string tempreg2 = context.GetFreeRegister("t",0,6);

            SetUniqueVarValue(context," arithoperand ");

            context.MapRegister(var_,tempreg2);

            OperationExecutor(stream,context,tempreg2,tempreg);

            context.SetarithconstinitFlag();
            //we dont reset the arithflag like we do in other cases here, as thats important to allow for correct constant initalization
        }

        if(Retwashigh){
            context.SetretFlag();
        }

    }
    else if(context.GetretFlag()){

        bool Retwashigh = false;
        if(context.GetretFlag()){
            context.ResetretFlag();
            Retwashigh = true;
        }

        std::string retreg;

        retreg = "a0";

        OperationExecutor(stream,context,retreg,tempreg);

        if(Retwashigh){
            context.SetretFlag();
        }

        context.ResetarithFlag();

    }
    else if(context.GetassignFlag()){

        bool Assignwashigh = false;
        if(context.GetassignFlag()){
            context.ResetassignFlag();
            Assignwashigh = true;
        }

        if(var_ != ""){
            stream << context.GetRegister(var_);
            context.FreeRegister(var_);
        }
        else{

            context.SetexpressionassignFlag();

            std::string tempreg2 = context.GetFreeRegister("t",0,6);

            SetUniqueVarValue(context," arithassign ");

            context.MapRegister(var_,tempreg2);

            OperationExecutor(stream,context,tempreg2, tempreg);

        }

        if(Assignwashigh){
            context.SetassignFlag();
        }

        context.ResetarithFlag();
    }
    else if(context.GetwhileFlag()){
        std::string retreg;

        retreg = context.GetRegister(" Conditional " + scopelevel);

        OperationExecutor(stream,context,retreg,tempreg);

        context.ResetarithFlag();

    }

    context.FreeRegister(" "); //frees termporary to be used again
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
