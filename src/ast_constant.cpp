#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context& context) const
{
    if(context.GetassignFlag() == true){
        stream << value_;
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
    else if(context.GetarithFlag() == true)
    {
        if(context.GetarithconstinitFlag() == true){
            std::string initreg;

            for(int i = 0; i < 7; i++){
                if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                    initreg = std::string("t") + std::to_string(i);
                    break;
                }
            }

            context.MapRegister(std::to_string(value_),initreg);

            stream << "li " << initreg << ", " << value_ << std::endl;
        }
        else{
            std::string tmpreg;
            tmpreg = context.GetRegister(std::to_string(value_));
            stream << tmpreg;
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
