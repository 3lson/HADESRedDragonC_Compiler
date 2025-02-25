#include "../../include/control_flow/ast_ifelse.hpp"
#include <iostream>

namespace ast {

void IfStatement::EmitRISC(std::ostream& stream, Context& context) const {
    condition_->EmitRISC(stream, context);

    std::string else_label = context.new_label("else");
    std::string end_label = context.new_label("end_if");

    stream << "beqz a0, " << else_label << std::endl;

    then_branch_->EmitRISC(stream, context);

    stream << "j " << end_label << std::endl;

    stream << else_label << ":" << std::endl;
    if (else_branch_) {
        else_branch_->EmitRISC(stream, context);
    }

    stream << end_label << ":" << std::endl;
}

void IfStatement::Print(std::ostream& stream) const {
    stream << "if (";
    condition_->Print(stream);
    stream << ") ";
    then_branch_->Print(stream);
    if (else_branch_) {
        stream << " else ";
        else_branch_->Print(stream);
    }
}

}
