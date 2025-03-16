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
    int dereference_num;

public:
    Variable() : isPointer(false), isArray(false), dataType(Type::_INT), scope(ScopeLevel::LOCAL), memoryOffset(0), arraySize(0), dereference_num(0) {}

    Variable(bool ptr, bool arr, Type type, int offset, int dereference_num)
    : isPointer(ptr), isArray(arr), dataType(type), scope(ScopeLevel::LOCAL), memoryOffset(offset), arraySize(1), dereference_num(dereference_num) {}

    Variable(bool ptr, bool arr, int size, Type type, int offset, int dereference_num)
    : isPointer(ptr), isArray(arr), dataType(type), scope(ScopeLevel::LOCAL), memoryOffset(offset), arraySize(size), dereference_num(dereference_num) {}

    Variable(bool ptr, bool arr, Type type, ScopeLevel scp, int dereference_num)
    : isPointer(ptr), isArray(arr), dataType(type), scope(scp), memoryOffset(0), arraySize(1), dereference_num(dereference_num) {}

    Variable(bool ptr, bool arr, int size, Type type, ScopeLevel scp, int dereference_num)
    : isPointer(ptr), isArray(arr), dataType(type), scope(scp), memoryOffset(0), arraySize(size), dereference_num(dereference_num) {}

    //Getters
    bool is_pointer() const { return isPointer; }
    bool is_array() const { return isArray; }
    Type get_type() const { return dataType; }
    ScopeLevel get_scope() const { return scope; }
    int get_offset() const { return memoryOffset; }
    int get_array_size() const { return arraySize; }
    int get_dereference_num() const {return dereference_num;}

    //Setters
    void set_pointer(bool ptr) {isPointer = ptr; }
    void set_array(bool arr) { isArray = arr; }
    void set_type(Type type) { dataType = type; }
    void set_scope(ScopeLevel scp) { scope = scp; }
    void set_offset(int offset) { memoryOffset = offset; }
    void set_dereference_num(int num) { dereference_num = num; }

};

class Global : public Variable {
    private:
        std::vector<uint32_t> lowerValues;
        std::vector<uint32_t> upperValues;

    public:
        Global() : Variable() {}
        Global(bool ptr, bool arr, Type type, int dereference_num) : Variable(ptr, arr, type, ScopeLevel::GLOBAL, dereference_num) {}
        Global(bool ptr, bool arr, int size, Type type, int dereference_num) : Variable(ptr, arr, size, type, ScopeLevel::GLOBAL, dereference_num) {}

        void print_global(std::ostream &stream) const;
        void push_lower(uint32_t value);
        void push_upper(uint32_t value);
    };
}//namespace ast
