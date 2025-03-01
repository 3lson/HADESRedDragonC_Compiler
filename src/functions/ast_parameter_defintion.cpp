#include "../../include/functions/ast_parameter_definition.hpp"

namespace ast{

void ParameterDefinition::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    const TypeSpecifier* type_specifier_ptr = dynamic_cast<const TypeSpecifier*>(type_specifier_.get());
    Type type = type_specifier_ptr->GetType();
    int offset = context.get_stack_offset();
    stream << context.store_instruction(type) << " " << dest_reg << ", " << offset << "(sp)" << std::endl;

    Variable variable_specs(false, false, type, ScopeLevel::LOCAL, offset);
    context.define_variable(GetIdentifier(), variable_specs);
    context.increase_stack_offset(types_size.at(type));
}

void ParameterDefinition::Print(std::ostream &stream) const{
    type_specifier_->Print(stream);
    stream << " ";
    declarator_->Print(stream);
}

void ParameterList::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const{
    int register_num;
    int start_register = 10; //parameter register a0 start
    std::string register_name;

    for (const auto& node : get_nodes())
    {
        const ParameterDefinition* parameter = dynamic_cast< const ParameterDefinition*>(node.get());

        //for integers - maybe used switch like for operations here?
        register_num = start_register++;
        register_name = context.get_register_name(register_num);
        parameter->EmitRISC(stream, context, register_name);
    }
    (void)dest_reg;

}

std::vector<Parameter> ParameterList::GetParameters(Context &context) const {
    int start_offset = context.get_stack_offset();
    std::vector<Parameter> parameters;

    for (const auto& node : get_nodes()) {
        const ParameterDefinition* parameter = dynamic_cast<const ParameterDefinition*>(node.get());
        Parameter Parameter = parameter->GetParameter(context, start_offset + GetOffset());
        parameters.push_back(Parameter);
    }
    return parameters;
}

int ParameterList::GetOffset() const {
    int newoffset = 0;
    for (const auto& param : get_nodes()) {
        const ParameterDefinition* param_def = dynamic_cast<const ParameterDefinition*>(param.get());

        Context dummy_context;
        newoffset += types_size.at(param_def->GetType(dummy_context));
    }
    return newoffset;
}

std::string ParameterDefinition::GetIdentifier() const
{
    const Identifier* identifier = dynamic_cast<const Identifier*>(declarator_.get());
    return identifier->GetIdentifier();
}

Type ParameterDefinition::GetType(Context &context) const
{
    const TypeSpecifier* type_specifier_ptr = dynamic_cast<const TypeSpecifier*>(type_specifier_.get());
    (void)context;
    return type_specifier_ptr->GetType();
}

Parameter ParameterDefinition::GetParameter(Context &context, int offset) const
{
    Type type = GetType(context);
    return Parameter(GetIdentifier(), false, false, type, offset);
}

int ParameterDefinition::GetTypeSize(Context &context) const
{
    return types_size.at(GetType(context));
}



}
