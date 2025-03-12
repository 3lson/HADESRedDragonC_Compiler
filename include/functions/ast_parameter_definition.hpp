#pragma once

#include "../ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../symbols/ast_identifier.hpp"

namespace ast{
class ParameterDefinition : public Node
{
private:
    NodePtr type_specifier_;
    NodePtr declarator_;

public:
    ParameterDefinition(NodePtr type_specifier, NodePtr declarator)
    : type_specifier_(std::move(type_specifier)), declarator_(std::move(declarator)) {}

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;
    Type GetType(Context &context) const;
    std::string GetIdentifier() const;
    int GetTypeSize(Context &context) const;
    Parameter GetParameter(Context &context, int offset) const;
};

class ParameterList : public NodeList
{
private:
    std::vector<Parameter> parameters;

public:
    using NodeList::NodeList;
    ~ParameterList() {}

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    int GetOffset() const;
    std::vector<Parameter> GetParameters(Context &context) const;


};
}
