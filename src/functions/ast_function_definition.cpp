#include "../../include/functions/ast_function_definition.hpp"
namespace ast {

void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Use dynamic_cast to const types to avoid casting away constness
    auto direct_declarator_ = dynamic_cast<const DirectDeclarator *>(declarator_.get()); // Use .get() to access the raw pointer
    if (!direct_declarator_) {
        throw std::runtime_error("Failed to cast declarator_ to DirectDeclarator");
    }

    std::string function_name = direct_declarator_->GetIdentifier();

    auto return_type_specifier = dynamic_cast<const TypeSpecifier *>(declaration_specifiers_.get());
    if (!return_type_specifier) {
        throw std::runtime_error("Failed to cast declaration_specifiers_ to TypeSpecifier");
    }
    Type return_type = return_type_specifier->GetType();

    stream << ".text" << std::endl;
    stream << ".globl " << function_name << std::endl;
    stream << ".type " << function_name << ", @function" << std::endl;
    stream << function_name << ":" << std::endl;

    // TODO: Create new function in context with arguments and return value
    ReturnValue return_value(false, false, return_type);
    std::vector<Argument> arguments = {};
    Function function(return_value, arguments);
    context.define_function(function_name, function);

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context, passed_reg);
    }
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
