#include "../../include/symbols/ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context& context) const
{

    std::string scopelevel = std::to_string(context.GetscopeLevel());

    if((context.GetassignFlag()) && !(context.GetarithFlag()) && (context.GetsecondcallFlag())){
        stream << value_;
    }
    else if(context.GetretFlag()){

        stream << "li a0, " << value_ << std::endl;

    }
    else if(context.GetequatingvarFlag()){
        //do nothing in this case
    }
    else if((context.GetarithFlag()) && !(context.GetarithconstinitFlag())){
        std::string reg = context.GetRegister(std::to_string(value_));
        stream << reg;
    }
    else if((context.GetarithconstinitFlag()) || (context.GetwhileFlag())) // or for singular constant condition (shortcut causes issues but fixed)
    {
        std::string initreg = context.GetFreeRegister("t",0,6);

        context.MapRegister(std::to_string(value_),initreg);

        stream << "li " << initreg << ", " << value_ << std::endl;

        if((context.GetwhileFlag()) && !(context.GetarithFlag())){
            std::string condreg =  context.GetRegister(" Conditional " + scopelevel);
            stream << "mv " << condreg << ", " << initreg << std::endl;
        }
    }
    else{
        stream << "li a0, " << value_ << std::endl;
    }

}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

} // namespace ast
