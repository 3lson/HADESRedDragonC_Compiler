#include "../../include/functions/ast_parameter_definition.hpp"

namespace ast{

void ParameterDefinition::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    Type type = GetType(context);
    int offset = context.get_stack_offset();
    stream << context.store_instr(type) << " " << dest_reg << ", " << offset << "(s0)" << std::endl;

    Variable variable(isPointer(), false, type, offset, GetDereference());
    context.define_variable(GetIdentifier(), variable);
    context.increase_stack_offset(GetTypeSize(context));
}

void ParameterDefinition::Print(std::ostream &stream) const{
    type_specifier_->Print(stream);
    stream << " ";
    declarator_->Print(stream);
}

void ParameterList::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const{
    int register_num;
    int int_register = 10; //parameter register a0 start
    int float_register = 42;
    std::string register_name;

    for (const auto& node : get_nodes())
    {
        if (!node){
            continue;
        }
        const ParameterDefinition* parameter = dynamic_cast< const ParameterDefinition*>(node.get());

        switch(parameter->GetType(context)){
            case Type::_CHAR:
            case Type::_SHORT:
            case Type::_INT:
            case Type::_UNSIGNED_INT:
            case Type::_LONG:
                register_num = int_register++;
                break;
            case Type::_FLOAT:
            case Type::_DOUBLE:
                register_num = float_register++;
                break;
            default:
                throw std::runtime_error("ParameterDefinition::EmitRISC - Invalid type");
        }

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
        Parameter Parameter = parameter->GetParameter(context, start_offset - GetOffset());
        parameters.push_back(Parameter);
    }
    return parameters;
}

int ParameterList::GetOffset() const {
    int size = 0;

    for (Parameter Parameter : parameters)
    {
        size += Parameter.GetTypeSize();

        // Align offset to 4 bytes
        if (size % 4 != 0)
        {
            size += 4 - (size % 4);
        }
    }
    return size;
}

std::string ParameterDefinition::GetIdentifier() const
{
    const Identifier* identifier = dynamic_cast<const Identifier*>(declarator_.get());
    const PointerDeclaration *pointer_declaration = dynamic_cast<const PointerDeclaration *>(declarator_.get());
    if (identifier){
        return identifier->GetIdentifier();
    }
    else if (pointer_declaration)
    {
        return pointer_declaration->GetIdentifier();
    }
    throw std::runtime_error("ParameterDeclaration::GetIdentifier() - declarator_ is not an Identifier or PointerDeclarator");
}

Type ParameterDefinition::GetType(Context &context) const
{
    const Specifier* type_specifier_ptr = dynamic_cast<const Specifier*>(type_specifier_.get());
    (void)context;
    return type_specifier_ptr->GetType();
}

Parameter ParameterDefinition::GetParameter(Context &context, int offset) const
{
    if (isPointer())
    {
        return Parameter(GetIdentifier(), true, false, GetType(context), offset, GetDereference());
    }
    return Parameter(GetIdentifier(), false, false, GetType(context), offset, 0);
}

int ParameterDefinition::GetTypeSize(Context &context) const
{
    if (isPointer()){
        types_size.at(Type::_INT);
    }
    return types_size.at(GetType(context));
}


bool ParameterDefinition::isPointer() const
{

    if (dynamic_cast<const PointerDeclaration *>(declarator_.get()))
    {
        return true;
    }

    return false;
}

int ParameterDefinition::GetDereference() const
{
    // Get dereference number for parameter
    const Declarator *declarator = dynamic_cast<const Declarator *>(declarator_.get());

    if (declarator)
    {
        return declarator->GetDereference();
    }

    return 0;
}


}
