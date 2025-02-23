#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context& context) const
{
    if((context.GetassignFlag() == true) && !(context.GetarithFlag()) && (context.GetsecondcallFlag())){
        stream << value_;
    }
    else if((context.GetassignFlag() == true) && (context.GetarithFlag()) && !(context.GetarithconstinitFlag())){
        std::string tmpreg;
        tmpreg = context.GetRegister(std::to_string(value_));
        stream << tmpreg;
    }
    else if(context.GetretFlag() == true){

        if(context.GetarithFlag() == true)
        {
            std::string tmpreg;
            tmpreg = context.GetRegister(std::to_string(value_));
            stream << tmpreg;
        }
        else{
            stream << "li a0, " << value_ << std::endl;
        }

    }
    else if(context.GetequatingvarFlag()){
        //do nothing in this case
    }
    else if((context.GetarithFlag()) && (context.GetwhileFlag()) && !(context.GetarithconstinitFlag())){
        std::string reg = context.GetRegister(std::to_string(value_));
        stream << reg;
    }
    else if(((context.GetarithFlag()) && (context.GetarithconstinitFlag())) || (context.GetwhileFlag())) // or for singular constant condition (shortcut causes issues but fixed)
    {
        std::string initreg;

        for(int i = 0; i < 7; i++){
            if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                initreg = std::string("t") + std::to_string(i);
                break;
            }
        }

        context.MapRegister(std::to_string(value_),initreg);

        stream << "li " << initreg << ", " << value_ << std::endl;

        if((context.GetwhileFlag()) && !(context.GetarithFlag())){
            std::string condreg =  context.GetRegister(" Conditional ");
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
