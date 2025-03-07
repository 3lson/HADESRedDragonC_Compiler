#pragma once

#include "../ast_node.hpp"
#include "../operations/ast_operand.hpp"

namespace ast{

class ArrayInitialization : public Node{
private:
    NodePtr initializer_list_;
public:
    ArrayInitialization(NodePtr initializer_list) : initializer_list_(std::move(initializer_list)) {}

    int GetArraySize() const;

    void SaveValue(std::ostream& stream, Context& context, int initial_offset, Type type) const;

    void EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const;
    void Print(std::ostream& stream) const;
};


}//namespace ast
