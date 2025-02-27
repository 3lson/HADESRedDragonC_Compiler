#pragma once

#include "../ast_node.hpp"

namespace ast{

class CompoundStatement : public NodeList
{
public:
    using NodeList::NodeList;
    ~CompoundStatement() = default;
    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
};

class StatementList : public NodeList
{
public:
    using NodeList::NodeList;
    ~StatementList() = default;
};

}
