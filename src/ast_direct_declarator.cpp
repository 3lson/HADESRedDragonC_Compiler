#include "../include/ast_direct_declarator.hpp"

namespace ast{

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    identifier_->EmitRISC(stream, context, dest_reg);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
    if (parameter_list_ != nullptr)
    {
        stream << "(";
        parameter_list_->Print(stream);
        stream << ")";
    }
}

std::string DirectDeclarator::GetIdentifier() const
{
    const Identifier *id = dynamic_cast<const Identifier *>(identifier_.get());
    const Declarator *declarator = dynamic_cast<const Declarator *>(identifier_.get());
    if (id != nullptr) {
        return id->GetIdentifier();
    } else if (declarator != nullptr){
        return declarator->GetIdentifier();
    }
    throw std::runtime_error("DirectDeclarator::GetIdentifier() - identifier_ is not an Identifier");

}

std::vector<Parameter> DirectDeclarator::GetParameters(Context &context) const
{
    if (parameter_list_ == nullptr)
    {
        return std::vector<Parameter>();
    }
    else
    {
        const ParameterList* parameter_list = dynamic_cast<const ParameterList*>(parameter_list_.get());
        return parameter_list->GetParameters(context);
    }
}

int DirectDeclarator::GetOffset() const
{
    if (parameter_list_ == nullptr)
    {
        return 0;
    }
    else
    {
        const ParameterList* parameter_list = dynamic_cast<const ParameterList*>(parameter_list_.get());
        return parameter_list->GetOffset();
    }
}


void DirectDeclarator::StoreParameters(std::ostream &stream, Context &context, std::string dest_reg) const
{
    if (parameter_list_ != nullptr)
    {
        const ParameterList *parameter_list = dynamic_cast<const ParameterList*>(parameter_list_.get());
        parameter_list->EmitRISC(stream, context, dest_reg);
    }
}

bool DirectDeclarator::isPointer() const
{
    return false;
}

int DirectDeclarator::GetDereference() const
{
    const Declarator *declarator = dynamic_cast<const Declarator *>(identifier_.get());
    if (declarator != nullptr)
    {
        return declarator->GetDereference();
    }

    return 0;
}

}//namespace ast
