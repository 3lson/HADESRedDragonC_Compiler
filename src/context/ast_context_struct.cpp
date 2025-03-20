#include "../../include/context/ast_context.hpp"

namespace ast{

void Context::struct_init(std::string identifier, std::unordered_map<std::string, Type>structMembers, std::unordered_map<std::string, int> structOffsets){
    structMap[identifier] = structMembers;
    structOffsetMap[identifier] = structOffsets;
}

std::unordered_map<std::string, Type> Context::get_struct_members(std::string identifier) const{
    return structMap.at(identifier);
}

std::unordered_map<std::string, int> Context::get_struct_offsets(std::string identifier) const {
    return structOffsetMap.at(identifier);
}

bool Context::is_struct(const std::string& identifier){
    return structMap.find(identifier) != structMap.end();
}

void Context::set_struct_size(std::string identifier, int size){
    structSizes[identifier] = size;
}

int Context::get_struct_size(const std::string& identifier) const{
    return structSizes.at(identifier);
}



}//namespace ast