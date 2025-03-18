#pragma once

#include "ast_node.hpp"

namespace ast{

class Declarator : public Node
{
public:
    virtual std::string GetId() const = 0;
    virtual std::vector<Parameter> GetParameters(Context &context) const = 0;
    virtual int GetOffset() const =0;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string dest_reg) const = 0;
    virtual bool isPointer() const = 0;
    virtual int GetDereference() const =0;

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override = 0;
    virtual void Print(std::ostream &stream) const override = 0;
};
}//namespace ast