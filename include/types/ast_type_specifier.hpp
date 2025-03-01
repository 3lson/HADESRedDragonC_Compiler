#pragma once
#include "ast_node.hpp"

namespace ast{

class TypeSpecifier : public Node
{
private:
    Type type_;

public:
    TypeSpecifier(Type type) : type_(type){};
    ~TypeSpecifier(){};

    Type GetType() const;
    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;
};

}//namespace ast
