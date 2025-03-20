#pragma once

#include "ast_node.hpp"

namespace ast{

class StructDeclaratorList : public NodeList{
public:
    using NodeList::NodeList;
    virtual ~StructDeclaratorList() override = default;
    std::string GetId() const;
};

}//namespace ast