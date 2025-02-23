#include "ast_while.hpp"
#include <iostream>

namespace ast {

    void WhileStatement::EmitRISC(std::ostream& stream, Context& context) const {
        // Generate labels for the loop
        context.SetwhileFlag();
        int while_label = context.GetwhileLabelCounter();
        context.IncrementwhileLabelCounter();
        std::string start_label = "start_loop_" + std::to_string(while_label);
        std::string end_label = "loop_end_" + std::to_string(while_label);

        // Emit the start label
        stream << start_label << ":" << std::endl;


        std::string condreg; //stores register upon which conditional statement is run

        for(int i = 0; i < 7; i++){
            if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                condreg = std::string("t") + std::to_string(i);
                break;
            }
        }

        //might consider using a higher scope level (we'll see ;) )
        context.MapRegister(" Conditional ", condreg);

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
    }


void WhileStatement::Print(std::ostream& stream) const {
    stream << "while (";
    condition_->Print(stream);
    stream << ") ";
    body_->Print(stream);
}

} // namespace ast
