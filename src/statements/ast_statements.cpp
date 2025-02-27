#include "../../include/statements/ast_statements.hpp"
namespace ast {

    void CompoundStatement::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
    {
        context.create_new_scope();
        for (const auto& statement : get_nodes())
        {
            statement->EmitRISC(stream, context, passed_reg);
        }
        context.pop_scope();
    }

    }

