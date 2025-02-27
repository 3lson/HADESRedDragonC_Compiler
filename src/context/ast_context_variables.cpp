#include "../../include/context/ast_context.hpp"

namespace ast{

//Define variable in the current scope
void Context::define_variable(const std::string& name, const Variable& var){
    if (variableStack.empty()){
        throw std::runtime_error("Error: Attempted to define variable in an empty scope.");
    }
    variableStack.back()[name] = var;
}

//Retreive a variable from the current or parent scopes
Variable Context::get_variable(const std::string& name) const {
    for(auto it = variableStack.rbegin(); it != variableStack.rend(); ++it){
        if(it->find(name) != it->end()){
            return it->at(name);
        }
    }
    throw std::runtime_error("Error: Variable '" + name + "' not found.");
}

}//namespace ast
