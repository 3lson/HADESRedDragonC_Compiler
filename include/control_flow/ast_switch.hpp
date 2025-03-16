#pragma once

#include "ast_node.hpp"
#include "../statements/ast_statements.hpp"
#include "../types/ast_type_specifier.hpp"
#include "../ast_direct_declarator.hpp"

namespace ast {

class SwitchStatement : public Node {
private:
    NodePtr condition_;
    NodePtr switch_cases_;

public:
    SwitchStatement(NodePtr condition, NodePtr switch_cases)
        : condition_(std::move(condition)), switch_cases_(std::move(switch_cases)) {}

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override;
    void Print(std::ostream& stream) const override;
};

class CaseStatement : public Node {
private:
    NodePtr condition_;
    NodePtr statement_list_;
public:
    CaseStatement(NodePtr condition, NodePtr statement_list, NodePtr value)
        : condition_(std::move(condition)), statement_list_(std::move(statement_list)){}

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override;
    void Print(std::ostream& stream) const override;
};

}
