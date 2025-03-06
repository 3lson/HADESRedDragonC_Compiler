#include "../../include/functions/ast_function_definition.hpp"
namespace ast {

void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    auto direct_declarator_ = dynamic_cast<const DirectDeclarator *>(declarator_.get());
    if (!direct_declarator_) {
        throw std::runtime_error("Failed to cast declarator_ to DirectDeclarator");
    }

    std::string function_name = direct_declarator_->GetIdentifier();

    auto return_type_specifier = dynamic_cast<const TypeSpecifier *>(declaration_specifiers_.get());
    if (!return_type_specifier) {
        throw std::runtime_error("Failed to cast declaration_specifiers_ to TypeSpecifier");
    }
    Type return_type = return_type_specifier->GetType();

    //Hard coding according to assembler directives
    stream << ".text" << std::endl;
    stream << ".globl " << function_name << std::endl;
    stream << ".type " << function_name << ", @function" << std::endl;
    stream << function_name << ":" << std::endl;

    ReturnValue return_value(false, false, return_type);
    //vector for my arguments to pull the arguments out then processing then in "pameter_definition"
    std::vector<Parameter> parameters = direct_declarator_->GetParameters(context);
    Function function(return_value, parameters);
    context.define_function(function_name, function);

    if (compound_statement_ != nullptr)
    {
        context.create_scope();
        context.push_operation_type(return_type);

        if (!compound_statement_) {
            throw std::runtime_error("Error: compound_statement_ is null in FunctionDefinition::EmitRISC");
        }

        const CompoundStatement *compound_statement = dynamic_cast<const CompoundStatement*>(compound_statement_.get());
        context.increase_stack_offset(8);
        int initial_offset = 8 + direct_declarator_->GetOffset();

        int stack_allocated_space = compound_statement->GetOffset(context) + initial_offset + 8;

        stream << "addi sp, sp, -" << stack_allocated_space << std::endl;
        stream << "sw ra, 0(sp)" <<std::endl;
        stream << "sw s0, 4(sp)" <<std::endl;
        direct_declarator_->StoreParameters(stream, context, dest_reg);
        stream << "addi s0, sp, " << stack_allocated_space <<std::endl;

        compound_statement_->EmitRISC(stream, context, dest_reg);

        stream << context.get_function_end() << ":" << std::endl;
        stream << "lw s0, 4(sp)" << std::endl;
        stream << "lw ra, 0(sp)" <<std::endl;
        stream << "addi sp, sp, " << stack_allocated_space <<std::endl;
        stream << "ret" << std::endl;

        context.pop_operation_type();
        context.pop_scope();
    }
    context.exit_function();
}

void FunctionDefinition::Print(std::ostream &stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
