#pragma once
#include "ast_context_types.hpp"

namespace ast{
enum class ScopeLevel {
    GLOBAL,
    LOCAL,
};

class Variable {
private:
    bool isPointer;
    bool isArray;
    Type dataType;
    ScopeLevel scope;
    int memoryOffset;

public:
    Variable() : isPointer(false), isArray(false), dataType(Type::_INT), scope(ScopeLevel::LOCAL), memoryOffset(0) {}
    Variable(bool ptr, bool arr, Type type, ScopeLevel scp, int offset)
    : isPointer(ptr), isArray(arr), dataType(type), scope(scp), memoryOffset(offset) {}


    //Getters
    bool is_pointer() const { return isPointer; }
    bool is_array() const { return isArray; }
    Type get_type() const { return dataType; }
    ScopeLevel get_scope() const { return scope; }
    int get_offset() const { return memoryOffset; }

    //Setters
    void set_pointer(bool ptr) {isPointer = ptr; }
    void set_array(bool arr) { isArray = arr; }
    void set_type(Type type) { dataType = type; }
    void set_scope(ScopeLevel scp) { scope = scp; }
    void set_offset(int offset) { memoryOffset = offset; }

};

}//namespace ast
