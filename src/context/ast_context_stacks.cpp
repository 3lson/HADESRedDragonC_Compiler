#include "../../include/context/ast_context.hpp"

namespace ast {

void Context::create_scope(){
    variableMap.push_back(std::unordered_map<std::string, Variable>());
    current_stack_offset.push(current_stack_offset.top());
}

void Context::pop_scope(){
    if (variableMap.empty()){
        throw std::runtime_error("Error: trying to pop empty scope");
    }
    variableMap.pop_back();
    current_stack_offset.pop();
}

int Context::get_stack_offset() const {
    return current_stack_offset.top();
}

void Context::increase_stack_offset(int offset){
    current_stack_offset.top() += offset;
}

}//namespace ast

