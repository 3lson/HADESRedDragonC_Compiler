#include "../../include/arrays/ast_array_initialization.hpp"

namespace ast{

int ArrayInitialization::GetArraySize() const
{
    return dynamic_cast<const NodeList *>(initializer_list_.get())->get_nodes().size();
}

void ArrayInitialization::EmitRISC(std::ostream &stream, Context &context, std::string dest_reg) const
{
    (void)stream;
    (void)context;
    (void)dest_reg;
}

void ArrayInitialization::Print(std::ostream &stream) const
{
    stream << "{ ";
    initializer_list_->Print(stream);
    stream << " }";
}

void ArrayInitialization::SaveValue(std::ostream &stream, Context &context, int initial_offset, Type type) const
{
    int offset = initial_offset;
    std::string dest_reg = context.get_register(type);

    for (const auto& initializer : dynamic_cast<const NodeList *>(initializer_list_.get())->get_nodes())
    {
        dynamic_cast<const Operand *>(initializer.get())->EmitRISC(stream, context, dest_reg);
        stream << context.store_instr(type) << " " << dest_reg << ", " << offset << "(sp)" << std::endl;

        offset += types_size.at(type);
    }

    context.deallocate_register(dest_reg);
}

}
