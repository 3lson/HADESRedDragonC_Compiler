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
    std::map<std::string,std::string> VarMap; //variable mapper from C to ASM registers
    int ifelseLabelCounter; // counts which branch of if-else you are in

public:
 //implement private attribute with getter methods instead

    Context() : retFlag(false), initFlag(false), assignFlag(false), ifelseLabelCounter(0){}

    //ifelseLabelCounter methods
    int GetifelseLabelCounter() const { return ifelseLabelCounter; }
    void IncrementifelseLabelCounter() { ifelseLabelCounter++; }

    //register flag methods
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
};

} // namespace ast
