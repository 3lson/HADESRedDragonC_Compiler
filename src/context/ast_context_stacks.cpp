#include "../../include/context/ast_context.hpp"

namespace ast {

void Context::create_new_scope(){
    variableStack.push_back(std::unordered_map<std::string, Variable>());
    current_stack_offset = 0;
}

void Context::pop_scope(){
    if (variableStack.empty()){
        throw std::runtime_error("Error: trying to pop empty scope");
    }
    variableStack.pop_back();
}

int Context::get_stack_offset() const {
    return current_stack_offset;
}

void Context::increase_stack_offset(int offset){
    current_stack_offset += offset;
}
}//namespace ast

