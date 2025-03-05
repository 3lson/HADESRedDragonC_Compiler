#pragma once

#include <vector>
#include <string>
#include "ast_context_types.hpp"

//Function, Parameter, ReturnValue Classes

namespace ast {

class ReturnValue
{
private:
    bool is_pointer_;
    bool is_array_;
    Type type;

public:
    ReturnValue() : is_pointer_(false), is_array_(false), type(Type::_INT) {}

    ReturnValue(bool is_pointer, bool is_array, Type type)
        : is_pointer_(is_pointer), is_array_(is_array), type(type) {}

    // Getters
    bool is_pointer() const { return is_pointer_; }
    bool is_array() const { return is_array_; }
    Type get_type() const { return type; }

    // Setters
    void set_pointer(bool ptr) { is_pointer_ = ptr; }
    void set_array(bool arr) { is_array_ = arr; }
    void set_type(Type t) { type = t; }
};

class Parameter
{
private:
    std::string name;
    bool is_pointer_;
    bool is_array_;
    Type type;
    int offset;

public:
    // Default constructor initializes to default values
    Parameter() : name(" whatever "), is_pointer_(false), is_array_(false), type(Type::_INT), offset(0) {}

    // Parameterized constructor
    Parameter(std::string name, bool is_pointer, bool is_array, Type type, int offset)
        : name(name), is_pointer_(is_pointer), is_array_(is_array), type(type), offset(offset) {}

    // Getters
    std::string get_name() const { return name; }
    bool is_pointer() const { return is_pointer_; }
    bool is_array() const { return is_array_; }
    Type get_type() const { return type; }
    int get_offset() const { return offset; }

    int GetTypeSize() const;

    // Setters
    void set_name(const std::string &n) { name = n; }
    void set_pointer(bool ptr) { is_pointer_ = ptr; }
    void set_array(bool arr) { is_array_ = arr; }
    void set_type(Type t) { type = t; }
    void set_offset(int off) { offset = off; }
};

class Function
{
private:
    ReturnValue return_value;
    std::vector<Parameter> parameters;

public:
    // Default constructor initializes the return value and parameters
    Function() : return_value(ReturnValue()), parameters(std::vector<Parameter>{}) {}

    // Parameterized constructor
    Function(ReturnValue return_value, std::vector<Parameter> parameters)
        : return_value(return_value), parameters(parameters) {}

    // Getters
    ReturnValue get_return_value() const { return return_value; }
    std::vector<Parameter> get_parameters() const { return parameters; }

    // Setters
    void set_return_value(const ReturnValue &rv) { return_value = rv; }
    void set_parameters(const std::vector<Parameter> &args) { parameters = args; }
};

}//namespace ast
