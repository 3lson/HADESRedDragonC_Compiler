#include "../../include/statements/ast_declaration.hpp"
namespace ast {

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    // Use dynamic_cast to a const pointer to avoid casting away constness
    const TypeSpecifier *type_specifier = dynamic_cast<const TypeSpecifier *>(type_specifier_.get());
    if (!type_specifier)
    {
        throw std::runtime_error("Declaration EmitRISC: Invalid type specifier");
    }

    Type type = type_specifier->GetType();
    int type_size = context.types_size.at(type);

    // Cast to const NodeList since declarator_list_ is a unique_ptr<const Node>
    const NodeList *declarator_list = dynamic_cast<const NodeList *>(declarator_list_.get());
    if (!declarator_list)
    {
        throw std::runtime_error("Declaration EmitRISC: Invalid declarator list");
    }

    for (const auto &declarator_ptr : declarator_list->get_nodes()) // Use const reference
    {
        // Now dynamic_cast to the const types
        const Assignment *assignment = dynamic_cast<const Assignment *>(declarator_ptr.get());
        const Identifier *identifier = dynamic_cast<const Identifier *>(declarator_ptr.get());

        int offset = context.get_stack_offset();
        context.increase_stack_offset(type_size);

        if (assignment != nullptr)
        {
            std::string variable_name = assignment->GetIdentifier();
            assignment->EmitRISC(stream, context, passed_reg);
            Variable variable_specs(false, false, type, ScopeLevel::LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }
        else if (identifier != nullptr)
        {
            std::string variable_name = identifier->GetIdentifier();
            Variable variable_specs(false, false, type, ScopeLevel::LOCAL, offset);
            context.define_variable(variable_name, variable_specs);
        }
        else
        {
            throw std::runtime_error("Declaration EmitRISC: Unknown declarator type");
        }
    }
}

void Declaration::Print(std::ostream &stream) const
{
    type_specifier_->Print(stream);
    stream << " ";

    declarator_list_->Print(stream);
    stream << ";" << std::endl;
}

}
