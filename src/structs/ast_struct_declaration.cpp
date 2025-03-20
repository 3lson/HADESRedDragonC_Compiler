#include "../../include/structs/ast_struct_declaration.hpp"

namespace ast{

void StructDeclaration::EmitRISC(std::ostream& stream, Context& context, std::string dest_reg) const {
    (void)stream;
    (void)dest_reg;
    std::cout << "Declaring struct variable: " << *variable_name_ << std::endl;
    std::cout << "Passing in struct type: " << *struct_type_ << std::endl;
    std::unordered_map<std::string, Type> members = context.get_struct_members(*struct_type_);
    int size =0;
    for (const auto& member: members){
        if (member.first.find("_offset") == std::string::npos){
            size += types_size.at(member.second);
        }
    }

    int offset = context.get_stack_offset();
    context.increase_stack_offset(size);

    Variable variable(false, false, size, Type::_STRUCT, offset, 0, *struct_type_);
    context.define_variable(*variable_name_, variable);
    std::cout << "Allocated " << size << " bytes on the stack for struct variable " << *variable_name_ << std::endl;
    context.set_struct_size(*variable_name_, size);

}

void StructDeclaration::Print(std::ostream& stream) const {
    stream << "struct " << *struct_type_ << " ";
}

std::string StructDeclaration::GetId() const{
    return *variable_name_;
}

Type StructDeclaration::GetType() const{
    return Type::_STRUCT;
}


}//namespace ast
