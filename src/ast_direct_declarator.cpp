#include "../include/ast_direct_declarator.hpp"

namespace ast{

void DirectDeclarator::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    identifier_->EmitRISC(stream, context, passed_reg);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream &stream) const
{
    identifier_->Print(stream);
}

std::string DirectDeclarator::GetIdentifier() const
{
    const Identifier *id = dynamic_cast<const Identifier *>(identifier_.get());
    if (id) {
        return id->GetIdentifier();
    }

    return "";
}
}//namespace ast
