#pragma once

#include "../ast_node.hpp"
#include <memory>

namespace ast {

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string *identifier) : identifier_(std::move(*identifier)){ delete identifier; };

    void EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const override;
    void Print(std::ostream &stream) const override;

    std::string GetIdentifier() const;

    Type GetType(Context &context) const;
};

}//namespace ast
