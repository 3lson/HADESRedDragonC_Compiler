#pragma once

#include "../ast_node.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../symbols/ast_constant.hpp"
#include "../pointers/ast_pointer_declaration.hpp"
#include "../ast_declarator.hpp"

namespace ast{

class ArrayDeclaration : public Declarator{
private:
    NodePtr identifier_;
    NodePtr constant_expression_;

public:
    ArrayDeclaration(NodePtr identifier, NodePtr constant_expression) : identifier_(std::move(identifier)), constant_expression_(std::move(constant_expression)) {}

    ArrayDeclaration(NodePtr identifier) : identifier_(std::move(identifier)), constant_expression_(nullptr) {}

    std::string GetId() const override;
    int GetArraySize(Context &context) const;
    bool isPointer() const override;

    virtual std::vector<Parameter>GetParameters(Context &context) const override;
    virtual void StoreParameters(std::ostream &stream, Context &context, std::string dest_reg) const override;
    virtual int GetOffset() const override;

    int GetDereference() const override;

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const;
    void Print(std::ostream& stream) const;
};

}
