#include "../../include/typedef/ast_typedef.hpp"

namespace ast{

void Typedef::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)stream;
    (void)context;
    (void)dest_reg;
    // left empty
}

void Typedef::Print(std::ostream &stream) const
{
    stream << "typedef ";
    declaration_specifier_->Print(stream);
    stream << " ";
}

void Typedef::DefineTypedef(NodeList *aliases)
{
    for (const auto& alias : aliases->get_nodes())
    {
        int pointer = initial_ptrs;
        std::string alias_name;

        const ArrayDeclaration *array_declaration = dynamic_cast<const ArrayDeclaration *>(alias.get());
        const Identifier *identifier = dynamic_cast<const Identifier *>(alias.get());
        const PointerDeclaration *pointer_declaration = dynamic_cast<const PointerDeclaration *>(alias.get());
        const AddressOf *address_of = dynamic_cast<const AddressOf *>(alias.get());

        if (array_declaration != nullptr)
        {
            alias_name = array_declaration->GetIdentifier();
            pointer += array_declaration->GetDereference();
            throw std::runtime_error("Typedef::DefineTypedef - ArrayDeclaration not implemented");
        }
        else if (identifier != nullptr)
        {
            alias_name = identifier->GetIdentifier();
        }
        else if( pointer_declaration != nullptr){
            pointer += pointer_declaration->GetDereference();
            alias_name = pointer_declaration->GetIdentifier();
        }
        else if (address_of != nullptr){
            pointer -= address_of->AddressCount();
            alias_name = address_of->GetIdentifier();
        }

        TypedefSpec typedef_spec;

        switch (type)
        {
        case Type::_STRUCT:
            throw std::runtime_error("Typedef::DefineTypedef - alias is not a PRIMITIVE");
        case Type::_CHAR:
        case Type::_SHORT:
        case Type::_UNSIGNED_INT:
        case Type::_INT:
        case Type::_LONG:
        case Type::_FLOAT:
        case Type::_DOUBLE:
            typedef_spec = TypedefSpec(type, pointer);
            break;
        default:
            throw std::runtime_error("Typedef::DefineTypedef - alias is not a PRIMITIVE nor a STRUCT");
        }

        // Call define_typedef on the context object
        context.define_typedef(alias_name, typedef_spec);
    }
}

void Typedef::GetDeclarationSpecifier()
{
    const Specifier *specifier = dynamic_cast<const Specifier *>(declaration_specifier_.get());

    if (specifier != nullptr)
    {
        type = specifier->GetType();
    }

    else
    {
        throw std::runtime_error("Typedef::ExtractDeclarationSpecifier - DeclarationSpecifier is not a typedef nor a standard specifier");
    }
}
}//namespace ast
