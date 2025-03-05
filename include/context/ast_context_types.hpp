#pragma once

namespace ast {
enum class Type
{
    _VOID,
    _CHAR,
    _SHORT,
    _UNSIGNED_INT,
    _INT,
    _LONG,
    _FLOAT,
    _DOUBLE,
};

//Defined in context.cpp now for universal use
extern const std::unordered_map<Type, int> types_size;
extern const std::unordered_map<Type, std::string> assembler_directives;

}//namespace ast
