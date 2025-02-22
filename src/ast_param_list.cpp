#include "ast_param_list.hpp"

namespace ast {

void ParamList::PushBack(NodePtr item)
{
    nodes_.push_back(std::move(item));
}

void ParamList::EmitRISC(std::ostream& stream, Context& context) const
{
    for (const auto& node : nodes_) //iterates over nodes
    {
        if (node == nullptr)
        {
            continue;
        }
        else{
            context.Incrementparam_num();
        }
        node->EmitRISC(stream, context);
    }
    context.Resetparam_num();
}

void ParamList::Print(std::ostream& stream) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}

}
