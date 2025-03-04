#include "../../include/statements/ast_statements.hpp"
namespace ast {

void CompoundStatement::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    context.set_initial_offset(context.get_stack_offset());
    context.create_new_scope();
    for (const auto& statement : get_nodes())
    {
        statement->EmitRISC(stream, context, dest_reg);
    }
    context.pop_scope();
}

int CompoundStatement::GetOffset(Context &context) const
{
    int offset = 0;
    for (const auto& node : get_nodes())
    {
        if (!node){
            continue;
        }
        const Statement *statement = dynamic_cast<const Statement *>(node.get());
        if (statement){
            offset += statement->GetOffset(context);
        }
        else {

        }
    }
    return offset;
}

int StatementList::GetOffset(Context &context) const
{
    (void)context;
    return 0;
}

int DeclarationList::GetOffset(Context &context) const
{
int offset = 0;
for (const auto& node : get_nodes())
{
    const Declaration *declaration = dynamic_cast<const Declaration *>(node.get());
    offset += declaration->GetOffset(context);
}
return offset;
}

}

