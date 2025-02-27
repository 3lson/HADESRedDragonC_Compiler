#include "../../include/context/ast_context.hpp"

namespace ast{
// Constructor
ContextRegister::ContextRegister(){
    register_file = {
        {0, Register("zero", Type::_INT, false)},
        {1, Register("ra", Type::_INT, false)},
        {2, Register("sp", Type::_INT, false)},
        {3, Register("gp", Type::_INT, false)},
        {4, Register("tp", Type::_INT, false)},
        {5, Register("t0", Type::_INT, true)},
        {6, Register("t1", Type::_INT, true)},
        {7, Register("t2", Type::_INT, true)},
        {8, Register("s0", Type::_INT, true)},
        {9, Register("s1", Type::_INT, true)},
        {10, Register("a0", Type::_INT, true)},
        {11, Register("a1", Type::_INT, true)},
        {12, Register("a2", Type::_INT, true)},
        {13, Register("a3", Type::_INT, true)},
        {14, Register("a4", Type::_INT, true)},
        {15, Register("a5", Type::_INT, true)},
        {16, Register("a6", Type::_INT, true)},
        {17, Register("a7", Type::_INT, true)},
        {18, Register("s2", Type::_INT, true)},
        {19, Register("s3", Type::_INT, true)},
        {20, Register("s4", Type::_INT, true)},
        {21, Register("s5", Type::_INT, true)},
        {22, Register("s6", Type::_INT, true)},
        {23, Register("s7", Type::_INT, true)},
        {24, Register("s8", Type::_INT, true)},
        {25, Register("s9", Type::_INT, true)},
        {26, Register("s10", Type::_INT, true)},
        {27, Register("s11", Type::_INT, true)},
        {28, Register("t3", Type::_INT, true)},
        {29, Register("t4", Type::_INT, true)},
        {30, Register("t5", Type::_INT, true)},
        {31, Register("t6", Type::_INT, true)},
    };

    // Mapping register to unique id reference for quick look-ups
    for (const auto& [key, reg] : register_file){
        register_name_to_int[reg.getName()] = key;
    }
}

// Destructor
ContextRegister::~ContextRegister() {}

// Get register method
std::string ContextRegister::get_register(Type type){
    for (auto& [key, reg] : register_file){
        if (reg.isAvailable()){
            reg.setAvailable(false);
            reg.setType(type);
            return reg.getName();
        }
    }
    throw std::runtime_error("No available register found!");
}

// Return register
std::string ContextRegister::get_return_register() const {
    return "a0";
}

// Deallocate Register
void ContextRegister::deallocate_register(const std::string &reg_name){
    if(register_name_to_int.find(reg_name) != register_name_to_int.end()){
        int reg_num = register_name_to_int[reg_name];
        register_file[reg_num].setAvailable(true);
        register_file[reg_num].setType(Type::_VOID);
    }
}

// Get register name from number
std::string ContextRegister::get_register_name(int reg_number) const {
    if(register_file.find(reg_number) != register_file.end()){
        return register_file.at(reg_number).getName();
    }
    throw std::runtime_error("Invalid register number!");
}

// Set register type
void ContextRegister::set_register_type(const std::string &reg_name, Type type){
    if (register_name_to_int.find(reg_name)!= register_name_to_int.end()){
        int reg_num = register_name_to_int[reg_name];
        register_file[reg_num].setType(type);
    }
}

}//namespace ast
