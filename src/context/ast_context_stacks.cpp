#include "../../include/context/ast_context.hpp"

namespace ast {

void Context::create_new_scope(){
    variableMap.push_back(std::unordered_map<std::string, Variable>());
    current_stack_offset = initial_stack_offset;
}

void Context::pop_scope(){
    if (variableMap.empty()){
        throw std::runtime_error("Error: trying to pop empty scope");
    }
    variableMap.pop_back();
}

int Context::get_stack_offset() const {
    return current_stack_offset;
}

void Context::increase_stack_offset(int offset){
    current_stack_offset += offset;
}

void Context::set_initial_offset(int offset){
    initial_stack_offset = offset;
}
}//namespace ast

