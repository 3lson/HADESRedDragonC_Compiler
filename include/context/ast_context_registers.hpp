#pragma once
#include <string>
#include <unordered_map>
#include <stack>
#include <set>
#include <iostream>
#include "ast_context_types.hpp"  // Ensure Type enum is available

namespace ast {

class Register {
private:
    bool is_available;   // Indicates if the register is free
    Type type;           // Register type (int, float, etc.)
    std::string reg_name; // Register name (e.g., "t0", "a1")

public:
    // Default constructor initializes as available and empty
    Register() : is_available(true), type(Type::_VOID), reg_name("") {}

    // Parameterized constructor
    Register(std::string name, Type type = Type::_VOID, bool available = true)
        : is_available(available), type(type), reg_name(std::move(name)) {}

    // Getters
    bool isAvailable() const { return is_available; }
    Type getType() const { return type; }
    const std::string& getName() const { return reg_name; }

    // Setters
    void setAvailable(bool available) { is_available = available; }
    void setType(Type newType) { type = newType; }
};

// The ContextRegister class manages register allocation/deallocation
class ContextRegister {
private:
    std::unordered_map<int, Register> register_file;
    std::unordered_map<std::string, int> register_name_to_int;
    std::stack<std::set<int>> allocated_registers;
    std::unordered_map<int, int> allocated_register_offsets;

public:
    ContextRegister();
    ~ContextRegister();

    std::string get_register(Type type);
    void deallocate_register(const std::string &reg_name);
    std::string get_register_name(int reg_number) const;
    void set_register_type(const std::string &reg_name, Type type);
    //void add_register_to_set(const std::string &reg_name);
    //void remove_register_from_set(const std::string &reg_name);
    //void push_registers(std::ostream &stream);
    //void pop_registers(std::ostream &stream);
};


}//namespace ast
