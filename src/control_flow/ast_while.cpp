#include "../../include/control_flow/ast_while.hpp"
#include <iostream>

namespace ast {

    void WhileStatement::EmitRISC(std::ostream& stream, Context& context) const {
        // Generate labels for the loop

        std::string scopelevel = std::to_string(context.GetscopeLevel());

        context.SetwhileFlag();
        std::string start_label = context.new_label("loop_start_");
        std::string end_label = context.new_label("loop_end_");

        // Emit the start label
        stream << start_label << ":" << std::endl;


        std::string condreg = context.GetFreeRegister("t",0,6); //stores register upon which conditional statement is run

        //might consider using a higher scope level (we'll see ;) )
        context.MapRegister(" Conditional " + scopelevel, condreg);

        condition_->EmitRISC(stream, context);

        // Emit the branch if the condition is false (i.e., break out of the loop)
        stream << "beqz " << condreg;
        // Emit the condition expression RISC code
        stream << ", " << end_label << std::endl; // Correct instruction

        context.SetlowerscopelevelFlag();
        // Emit the body of the while loop
        body_->EmitRISC(stream, context);

        context.ResetlowerscopelevelFlag();

        // Jump back to the start of the loop to recheck the condition
        stream << "j " << start_label << std::endl;

        // Emit the end label for the while loop
        stream << end_label << ":" << std::endl;
        context.ResetwhileFlag();

        context.FreeRegister(" Conditional " + scopelevel);

    }


void WhileStatement::Print(std::ostream& stream) const {
    stream << "while (";
    condition_->Print(stream);
    stream << ") ";
    body_->Print(stream);
}

} // namespace ast
