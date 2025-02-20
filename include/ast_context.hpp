#pragma once

#include <map>
#include <string>
namespace ast {
class Context
{
private:
    bool retFlag; //return statement flag
    bool initFlag; // initialization of variables flag
    bool assignFlag; // Assignment flag
    bool funcFlag; // function flag to know when executing inside a function
    bool paramFlag; // parameter flag to know when initializing a parameter
    std::map<std::string,std::string> VarMap; //variable mapper from C to ASM registers
    int ifelseLabelCounter; // counts which branch of if-else you are in
    bool arithFlag; // arithmetic expression flag
    bool arithconstinitFlag; // constant arithmatic initialization flag

public:
 //implement private attribute with getter methods instead

    Context() : retFlag(false), initFlag(false), assignFlag(false), funcFlag(false),
    paramFlag(false), ifelseLabelCounter(0), arithFlag(0), arithconstinitFlag(false){}

    //arithmetic const expressions methods
    bool GetarithconstinitFlag() const { return arithconstinitFlag; }
    void SetarithconstinitFlag(){ arithconstinitFlag = true; }
    void ResetarithconstinitFlag(){ if(arithconstinitFlag == true){ arithconstinitFlag = false; } }

    //arithmetic expressions methods
    bool GetarithFlag() const { return arithFlag; }
    void SetarithFlag(){ arithFlag = true; }
    void ResetarithFlag(){ if(arithFlag == true){ arithFlag = false; } }

    //ifelseLabelCounter methods
    int GetifelseLabelCounter() const { return ifelseLabelCounter; }
    void IncrementifelseLabelCounter() { ifelseLabelCounter++; }

    //function flag methods
    bool GetfuncFlag() const { return funcFlag; }
    void SetfuncFlag(){ funcFlag = true; }
    void ResetfuncFlag(){ if(funcFlag == true){ funcFlag = false; } }

    //parameter flag methods
    bool GetparamFlag() const { return paramFlag; }
    void SetparamFlag(){ paramFlag = true; }
    void ResetparamFlag(){ if(paramFlag == true){ paramFlag = false; } }

    //return flag methods
    bool GetretFlag() const { return retFlag; }
    void SetretFlag(){ retFlag = true; }
    void ResetretFlag(){ if(retFlag == true){ retFlag = false; } }

    //initflag methods
    bool GetinitFlag() const { return initFlag; }
    void SetinitFlag(){ initFlag = true; }
    void ResetinitFlag(){ if(initFlag == true){ initFlag = false; } }

    //Assignment flag methods
    bool GetassignFlag() const { return assignFlag; }
    void SetassignFlag(){ assignFlag = true; }
    void ResetassignFlag(){ if(assignFlag == true){ assignFlag = false; } }


    //register management methods
    std::string GetRegister(const std::string& var) const{
        return VarMap.at(var);
    }
    void MapRegister(const std::string& var, const std::string& Reg) {
        VarMap[var] = Reg;
    }
    bool RegisterInUse(const std::string& Reg) const {

        for(const auto& pair : VarMap){
            if(pair.second == Reg){
                return true;
            }
        }
        return false;
    }
};

} // namespace ast
