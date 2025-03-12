#include "../../include/statements/ast_declaration.hpp"
namespace ast {

void Declaration::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    const Specifier *specifier = dynamic_cast<const Specifier*>(type_specifier_.get());
    specifier->DefineSpecifier(context);

    if (declarator_list_ == nullptr)
    {
        return;
    }

    Type type = GetType();
    int type_size = types_size.at(type);

    // Cast to const NodeList since declarator_list_ is a unique_ptr<const Node>
    const NodeList *declarator_list = dynamic_cast<const NodeList *>(declarator_list_.get());

    for (const auto &declarator_ptr : declarator_list->get_nodes()) // Use const reference
    {
        // Dynamic ast different declaration types
        const Assignment *assignment = dynamic_cast<const Assignment *>(declarator_ptr.get());
        const Identifier *identifier = dynamic_cast<const Identifier *>(declarator_ptr.get());
        const DirectDeclarator *direct_declarator = dynamic_cast<const DirectDeclarator *>(declarator_ptr.get());
        const ArrayDeclaration * array_declaration = dynamic_cast<const ArrayDeclaration *>(declarator_ptr.get());

        int offset = context.get_stack_offset();

        if (assignment != nullptr)
        {
            int array_size = assignment->GetArraySize(context);
            bool is_array = assignment->isArrayInitialization();
            context.increase_stack_offset(type_size * array_size);
            std::string variable_name = assignment->GetIdentifier();
            Variable variable(false, is_array, array_size, type, offset);
            context.define_variable(variable_name, variable);
            assignment->EmitRISC(stream, context, dest_reg);
        }
        else if (identifier != nullptr)
        {
            context.increase_stack_offset(type_size);
            std::string variable_name = identifier->GetIdentifier();
            Variable variable(false, false, type, offset);
            context.define_variable(variable_name, variable);
        }
        else if (direct_declarator != nullptr)
        {
            std::string function_name = direct_declarator->GetIdentifier();

            ReturnValue return_value = ReturnValue(false, false, type);
            std::vector<Parameter> parameters = direct_declarator->GetParameters(context);
            Function function = Function(return_value, parameters);

            context.define_function(function_name, function);
        }
        else if (array_declaration != nullptr)
        {
            int array_size = array_declaration->GetArraySize(context);

            if (array_declaration->GetArraySize(context) == -1)
            {
                throw std::runtime_error("Declaration EmitRISC: Array size not specified");
            }

            context.increase_stack_offset(type_size * array_size);

            std::string variable_name = array_declaration->GetIdentifier();

            Variable variable(false, true, array_size, type, offset);
            context.define_variable(variable_name, variable);
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

    if (declarator_list_)
    {
        declarator_list_->Print(stream);
    }
    stream << ";" << std::endl;
}

int Declaration::GetOffset(Context &context) const
{
    (void)context;
    const Specifier *type_specifier = dynamic_cast<const Specifier*>(type_specifier_.get());
    if (!type_specifier) {
        throw std::runtime_error("Declaration::GetOffset: Invalid type specifier");
    }
    Type type = type_specifier->GetType();
    int type_size = types_size.at(type);

    const NodeList *declarator_list = dynamic_cast<const NodeList *>(declarator_list_.get());

    int total_size = 0;

    if (declarator_list_ != nullptr)
    {
        for (const auto &declarator : declarator_list->get_nodes()) {
            const Assignment *assignment = dynamic_cast<const Assignment *>(declarator.get());
            const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(declarator.get());
            const Identifier *identifier = dynamic_cast<const Identifier*>(declarator.get());

            if (assignment != nullptr) {
                if (assignment->isArrayInitialization()) {
                    total_size += type_size * assignment->GetArraySize(context);
                } else {
                    total_size += type_size;
                }
            } else if (array_declaration != nullptr) {
                total_size += type_size * array_declaration->GetArraySize(context);
            } else if (identifier != nullptr) {
                type_size = total_size + type_size;
            }
        }
    }
    return total_size;
}

Type Declaration::GetType() const {
    const Specifier *type_specifier = dynamic_cast<const Specifier *>(type_specifier_.get());
    if (!type_specifier)
    {
        throw std::runtime_error("Declaration EmitRISC: Invalid type specifier");
    }

    return type_specifier->GetType();
}

void Declaration::DeclareGlobal(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)dest_reg;

    const Specifier *specifier = dynamic_cast<const Specifier *>(type_specifier_.get());
    specifier->DefineSpecifier(context);

    if (declarator_list_ == nullptr)
    {
        return;
    }
    Type type = GetType();
    //int type_size = types_size.at(type);

    const NodeList *declarator_list = dynamic_cast<const NodeList *>(declarator_list_.get());
    for (const auto& declarator : declarator_list->get_nodes())
    {
        const Assignment *assignment = dynamic_cast<const Assignment *>(declarator.get());
        const Identifier *identifier = dynamic_cast<const Identifier *>(declarator.get());
        const DirectDeclarator *direct_declarator = dynamic_cast<const DirectDeclarator *>(declarator.get());
        const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(declarator.get());

        //int offset = context.get_stack_offset();

        if (assignment != nullptr)
        {
            int array_size = assignment->GetArraySize(context);

            bool is_array = assignment->isArrayInitialization();

            std::string global_name = assignment->GetIdentifier();
            Global global(false, is_array, array_size, type);
            assignment->InitializeGlobals(stream, context, global);
            context.define_global(global_name, global);
        }

        else if (identifier != nullptr)
        {
            std::string global_name = identifier->GetIdentifier();

            Global global = Global(false, false, type);
            context.define_global(global_name, global);
        }

        else if (array_declaration != nullptr)
        {
            int array_size = array_declaration->GetArraySize(context);

            if (array_declaration->GetArraySize(context) == -1)
            {
                throw std::runtime_error("Declaration EmitRISC: Array size not specified");
            }

            std::string global_name = array_declaration->GetIdentifier();

            Global global(false, true, array_size, type);
            context.define_global(global_name, global);
        }

        else if (direct_declarator != nullptr)
        {
            std::string function_name = direct_declarator->GetIdentifier();

            ReturnValue return_value = ReturnValue(false, false, type);
            std::vector<Parameter> arguments = direct_declarator->GetParameters(context);

            Function function = Function(return_value, arguments);
            context.define_function(function_name, function);
        }

        else
        {
            throw std::runtime_error("Declaration DeclareGlobal: Unknown declarator type");
        }
    }
}

}
