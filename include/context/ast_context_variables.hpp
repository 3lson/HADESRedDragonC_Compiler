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
    int arraySize;

public:
    Variable() : isPointer(false), isArray(false), dataType(Type::_INT), scope(ScopeLevel::LOCAL), memoryOffset(0), arraySize(0) {}

    Variable(bool ptr, bool arr, Type type, int offset)
    : isPointer(ptr), isArray(arr), dataType(type), scope(ScopeLevel::LOCAL), memoryOffset(offset), arraySize(1) {}

    Variable(bool ptr, bool arr, int size, Type type, int offset)
    : isPointer(ptr), isArray(arr), dataType(type), scope(ScopeLevel::LOCAL), memoryOffset(offset), arraySize(size) {}

    Variable(bool ptr, bool arr, Type type, ScopeLevel scp)
    : isPointer(ptr), isArray(arr), dataType(type), scope(scp), memoryOffset(0), arraySize(1) {}

    Variable(bool ptr, bool arr, int size, Type type, ScopeLevel scp)
    : isPointer(ptr), isArray(arr), dataType(type), scope(scp), memoryOffset(0), arraySize(size) {}

    //Getters
    bool is_pointer() const { return isPointer; }
    bool is_array() const { return isArray; }
    Type get_type() const { return dataType; }
    ScopeLevel get_scope() const { return scope; }
    int get_offset() const { return memoryOffset; }
    int get_array_size() const { return arraySize; }

    //Setters
    void set_pointer(bool ptr) {isPointer = ptr; }
    void set_array(bool arr) { isArray = arr; }
    void set_type(Type type) { dataType = type; }
    void set_scope(ScopeLevel scp) { scope = scp; }
    void set_offset(int offset) { memoryOffset = offset; }

};

class Global : public Variable {
    private:
        std::vector<uint32_t> lowerValues;
        std::vector<uint32_t> upperValues;

    public:
        Global() : Variable() {}
        Global(bool ptr, bool arr, Type type) : Variable(ptr, arr, type, ScopeLevel::GLOBAL) {}
        Global(bool ptr, bool arr, int size, Type type) : Variable(ptr, arr, size, type, ScopeLevel::GLOBAL) {}

        void print_global(std::ostream &stream) const;
        void push_lower(uint32_t value);
        void push_upper(uint32_t value);
    };
}//namespace ast
