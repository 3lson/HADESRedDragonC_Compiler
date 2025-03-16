#pragma once

#include "../ast_node.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../ast_direct_declarator.hpp"
#include "../ast_declarator.hpp"

namespace ast{

class PointerDeclaration : public Declarator
{
private:
    NodePtr direct_declarator_;

public:
    PointerDeclaration(NodePtr direct_declarator) : direct_declarator_(std::move(direct_declarator)) {}

    std::string GetIdentifier() const override;
    Type GetType() const;

    virtual std::vector<Parameter>GetParameters(Context &context) const override;
    virtual int GetOffset() const override;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string dest_reg) const override;
    virtual bool isPointer() const override;
    int GetDereference() const override;

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;
};
}//namespace ast