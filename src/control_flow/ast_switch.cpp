#include "../../include/control_flow/ast_switch.hpp"


namespace ast {

    void SwitchStatement::EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const {

        std::string condition_reg = context.get_register(Type::_INT);

        condition_->EmitRISC(stream, context, condition_reg);

        const CompoundStatement *compound_statement = dynamic_cast<const CompoundStatement*>(switch_cases_.get());

        int cases = compound_statement->GetCases(context);



    }

    void SwitchStatement::Print(std::ostream& stream) const {

    }

    void CaseStatement::EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const {

    }

    void CaseStatement::Print(std::ostream& stream) const {

    }

 }
