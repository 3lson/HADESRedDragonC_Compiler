#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <set>

#include "ast_context_types.hpp"
#include "ast_context_registers.hpp"
#include "ast_context_functions.hpp"
#include "ast_context_variables.hpp"
#include "ast_context_mode.hpp"

namespace ast {

class Context
{
private:
    // ----- Register Management ------
    ContextRegister reg_manager;

    // ----- Stack Management -----
    int current_stack_offset;

    // ----- Variable Management ------
    std::vector<std::unordered_map<std::string, Variable>> variableStack;

    // ------ Function Management -------
    std::unordered_map<std::string, Function> function_bindings;
    std::string last_function_end_statement;
    std::string return_register;

    // ------ Control Flow Management ------
    int label_counter;
    std::stack<std::string> start_labels;
    std::stack<std::string> end_labels;

    // --------- Mode tracking (Flag replacement) -------
    std::stack<Mode> mode_stack;

    // ------ Type tracking -------
    std::stack<Type> operation_type_stack;

public:
    Context();
    ~Context();

    // ---------- Register Management --------------
    std::string get_register(Type type) { return reg_manager.get_register(type); }
    std::string get_return_register() const { return reg_manager.get_return_register(); }
    void deallocate_register(const std::string &reg_name) { reg_manager.deallocate_register(reg_name); }
    std::string get_register_name(int reg_number) const {return reg_manager.get_register_name(reg_number); }
    void set_register_type(const std::string &reg_name, Type type) { reg_manager.set_register_type(reg_name, type); }


    // --------- Variable Management --------

    void define_variable(const std::string& name, const Variable& var);
    Variable get_variable(const std::string& name) const;

    // --------- Scope Management ---------
    void create_new_scope();
    void pop_scope();

    int get_stack_offset() const;
    void increase_stack_offset(int offset);

    // --------- Function Management ---------
    void define_function(std::string identifier, Function function);
    Function get_function(std::string identifier) const;
    std::string get_last_function_end_statement() const;
    void set_return_register(Type type);

    // ------ Control Flow Management --------
    std::string create_label(std::string id);

    // Label saving and fetching for control flow
    void save_start_label(std::string label);
    void save_end_label(std::string label);
    void pop_start_label();
    void pop_end_label();
    std::string get_start_label() const;
    std::string get_end_label() const;

    // --------- Move, store and load instructions ------
    std::string move_instruction(Type type) const;
    std::string store_instruction(Type type) const;
    std::string load_instruction(Type type) const;

    // ---------- Mode management --------
    void mode_push(Mode mode);
    void mode_pop();
    bool has_mode(Mode mode) const;

    // -------- Type specific properties ----------
    static const std::unordered_map<Type, int> types_size;
    static const std::unordered_map<Type, std::string> assembler_directives;

};

}//namespace ast
