#pragma once

#include "ast_node.hpp"

namespace ast{

class FlowManagement : public Node{
public:
    FlowManagement() {}

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const override = 0;
    void Print(std::ostream& stream) const override = 0;
};
}
