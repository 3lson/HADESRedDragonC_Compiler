#include "ast_identifier.hpp"

namespace ast {

//noticibily i have avoided throwing compiler error when an empty register is not found (this might be worth implementing later)

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    if(context.GetretFlag() == true){

        std::string reg = context.GetRegister(identifier_);

        if(context.GetarithFlag() == true){
            stream << reg;
        }
        else{
            if(context.GetparamFlag() == true){
                stream << "addi a1, " << reg << ", 0" << std::endl;
            }
            else{
                stream << "addi a0, " << reg << ", 0" << std::endl;
            }
        }

    }
    else if(context.GetinitFlag() == true){
        std::string initreg; //stores the correct initialization register

        //assign variable to temporaries (t0 - t6) or function argument (a2 - a7)
        if(context.GetfuncFlag() == true){
            //parameter assignment (a0 - a7)
            if(context.GetparamFlag() == true){

                for(int i = 0;  i < 8; i++){
                    if(context.RegisterInUse(std::string("a") + std::to_string(i)) == false){
                        initreg = std::string("a") + std::to_string(i);
                    }
                }

            }
            //local temporaries assignment (t0 - t6)
            else{
                for(int i = 0; i < 7; i++){
                    if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                        initreg = std::string("t") + std::to_string(i);
                        break;
                    }
                }
            }
        }
        //global assignment (s1 - s11)
        else {
            for(int i = 1; i < 12; i++){
                if(context.RegisterInUse(std::string("s") + std::to_string(i)) == false){
                    initreg = std::string("s") + std::to_string(i);
                    break;
                }
            }
        }
        context.MapRegister(identifier_,initreg);
        stream << "li " << initreg << ", " << "0" << std::endl; //uses temporary register (t0 assumes local scope)
    }
    else if(context.GetassignFlag() == true){
        std::string reg = context.GetRegister(identifier_);
        stream << "li " << reg << ", ";
    }
    else if(context.GetarithFlag() == true){
        if(context.GetarithconstinitFlag() == true){
        }
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
