#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    if(context.GetretFlag() == true){
        std::string reg = context.GetRegister(identifier_);
        stream << "addi a0, " << reg << ", 0" << std::endl;
    }
    else if(context.GetinitFlag() == true){
        context.MapRegister(identifier_,"t0");
        stream << "li t0, " << "0" << std::endl; //uses temporary register (t0 assumes local scope)
    }
    else if(context.GetassignFlag() == true){
        std::string reg = context.GetRegister(identifier_);
        stream << "li " << reg << ", ";
    }
    else{
        stream << identifier_;
    }
}

void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;
};

}
