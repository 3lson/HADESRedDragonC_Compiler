#include "../../include/context/ast_context.hpp"

namespace ast{

void Context::define_enum(std::string name, std::vector<std::string> labels){
    enumsDefinitions[name] = labels;
}

void Context::define_enum_label(std::string label, int value){
    if (enumMap.empty()){
        throw std::runtime_error("Context::define_enum_label - No active scope");
    }
    enumMap.back()[label] = value;
}

bool Context::is_enum(std::string identifier){
    for (auto it = enumMap.rbegin(); it != enumMap.rend(); ++it){
        if (it->find(identifier) != it->end()){
            return true;
        }
    }
    return false;
}

int Context::get_enum_label(std::string label){
    for (auto it = enumMap.rbegin(); it != enumMap.rend(); ++it){
        if (it->find(label) != it->end()){
            return it->at(label);
        }
    }
    throw std::runtime_error("Context::GetEnumValue - enum value not found");
}


}//namespace ast
