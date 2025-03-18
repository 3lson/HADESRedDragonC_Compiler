#pragma once

#include "ast_node.hpp"
#include "../specifiers/ast_specifier.hpp"
#include "../symbols/ast_identifier.hpp"
#include "../context/ast_context.hpp"

namespace ast{

class StructSpecifier : public Specifier{
private:
    std::string *name_;
    NodeList* declarations;

public:
    StructSpecifier(std::string *name, NodeList* declarations) : name_(name), declarations(declarations) {}
    StructSpecifier(std::string *name) : name_(name), declarations(nullptr) {}
    StructSpecifier(NodeList* declarations) : name_(nullptr), declarations(declarations) {}
    ~StructSpecifier() {
        if (name_){
            delete name_;
        }
        if (declarations) {
            delete declarations;
        }
    }

    void DefineSpecifier(Context& context) const override;
    virtual Type GetType() const override;
    virtual void Print(std::ostream& stream) const override;


};
}//namespace ast