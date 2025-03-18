#pragma once

#include "ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../context/ast_context.hpp"

namespace ast{

class StructSpecifier : public Specifier{
private:
    std::string name;
    NodeList* declarations;

public:
    StructSpecifier(const std::string& name, NodeList* declarations) : name(name), declarations(declarations) {}
    ~StructSpecifier() {
        if (declarations) {
            delete declarations;
        }
    }

    void DefineSpecifier(Context& context) const override;
    virtual Type GetType() const override;
    virtual void Print(std::ostream& stream) const override;


};
}//namespace ast