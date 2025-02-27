#pragma once

#include "../ast_node.hpp"
#include <memory>

namespace ast {

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string identifier) : identifier_(std::move(identifier)){};

    void EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;
};

}//namespace ast
