#include "ast_identifier.hpp"

namespace ast {

std::string Identifier::GetResolvedRegister(const Context& context) const{
    std::string scopelevel = std::to_string(context.GetscopeLevel());
    std::string reg;
    if(context.GetlowerscopelevelFlag()){
        int scopeLevelnum = context.GetscopeLevel();
        for(int i = scopeLevelnum; i > 0; i--){
            reg = context.GetRegister(identifier_ + std::to_string(i));
            if(reg != ""){
                break;
            }
        }
    }
    else{
        reg = context.GetRegister(identifier_ + scopelevel);
    }

    return reg;
}

//noticibily i have avoided throwing compiler error when an empty register is not found (this might be worth implementing later)

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{

    std::string scopelevel = std::to_string(context.GetscopeLevel());
    if(context.GetretFlag() == true){

        std::string reg;
        //reg = context.GetRegister(identifier_ + scopelevel);

        reg = GetResolvedRegister(context);

        if(context.GetarithFlag() == true){
            stream << reg;
        }
        else{
            stream << "addi a0, " << reg << ", 0" << std::endl;
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

                context.MapRegister(identifier_ + scopelevel,initreg);
                stream << "addi " << initreg << ", " << "a" << context.Getparam_num() << ", 0" << std::endl; //uses temporary register (t0 assumes local scope)


            }
            //local temporaries assignment (t0 - t6)
            else{
                for(int i = 0; i < 7; i++){
                    if(context.RegisterInUse(std::string("t") + std::to_string(i)) == false){
                        initreg = std::string("t") + std::to_string(i);
                        break;
                    }
                }

                context.MapRegister(identifier_ + scopelevel,initreg);
                stream << "li " << initreg << ", " << "0" << std::endl; //uses temporary register (t0 assumes local scope)
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

            context.MapRegister(identifier_ + scopelevel,initreg);
            stream << "li " << initreg << ", " << "0" << std::endl; //uses temporary register (t0 assumes local scope)
        }


        if(context.GetassignFlag() == true){

            std::string assignreg = GetResolvedRegister(context);

            if(context.GetidentifierassignFlag()&& !(context.GetequatingvarFlag())){
                stream << "addi " << assignreg << ", ";
            }
            else if((context.GetequatingvarFlag()) && (context.GetidentifierassignFlag()) ){
                stream << assignreg << ", 0";
            }
            else if(context.GetexpressionassignFlag()){
                stream << "mv "  << assignreg << ", ";
            }
            else{
                stream << "li " << assignreg << ", ";
            }
        }
    }
    else if((context.GetequatingvarFlag()) && !(context.GetidentifierassignFlag())){
        context.SetidentifierassignFlag();
    }
    else if((context.GetassignFlag()) && !(context.GetinitFlag()) && !(context.GetarithFlag())){
        std::string reg = GetResolvedRegister(context);

        if((context.GetidentifierassignFlag()) && !(context.GetequatingvarFlag())){
            stream << "addi " << reg << ", ";
        }
        else if((context.GetequatingvarFlag()) && (context.GetidentifierassignFlag()) ){
            stream << reg << ", 0";
        }
        else if(context.GetexpressionassignFlag()){
            stream << "mv "  << reg << ", ";
        }
        else{
            stream << "li " << reg << ", ";
        }

    }
    else if(context.GetarithFlag()){

        if(context.GetarithconstinitFlag() == true){
            //nothing happens here as variable is already initialized
        }
        else if(context.GetassignFlag()){
            std::string reg = GetResolvedRegister(context);
            stream << reg;
        }
        else if(context.GetwhileFlag()){
            std::string reg = GetResolvedRegister(context);
            stream << reg;
        }
    }
    else{
        //function declarator
        if (context.GetwhileFlag() == true){
            std::string reg = GetResolvedRegister(context);
            std::string condreg =  context.GetRegister(" Conditional ");
            stream << "mv " << condreg <<", "<< reg << std::endl;
        } else{
            stream << identifier_;
        }
    }
}

void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;
};

}
