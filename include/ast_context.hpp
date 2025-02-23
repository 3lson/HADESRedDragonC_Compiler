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
    bool equatingvarFlag; // used such that variables values can be assigned to each other.
    bool identifierassignFlag; //secondary flag to equatingvarFlag that is set inside identifier.
    bool expressionassignFlag; //flag that identifies that we are assigning an expression
    bool secondcallFlag; //flag that used in assignment operator to indicate value has been called a second time
    int scopeLevel; //flag that tracks the scope level
    int param_num; //keeps track of function argument number
    int whileLabelCounter; // counts which branch of while you are in
    bool whileIdentifierFlag; //This overwrites compounds and identifier cases in while loop condition cases
    bool lowerscopelevelFlag; // used in while and if statements to allow for variable access in lower and same scope levels

public:
 //implement private attribute with getter methods instead

    Context() : retFlag(false), initFlag(false), assignFlag(false), funcFlag(false),
    paramFlag(false), ifelseLabelCounter(0), arithFlag(0), arithconstinitFlag(false),
    equatingvarFlag(false), identifierassignFlag(false), expressionassignFlag(false),
    secondcallFlag(false),scopeLevel(0), param_num(-1), whileLabelCounter(0),
    whileIdentifierFlag(false), lowerscopelevelFlag(false){}

    //while condition for condition evaluation
    bool GetlowerscopelevelFlag() const { return lowerscopelevelFlag; }
    void SetlowerscopelevelFlag(){ lowerscopelevelFlag = true; }
    void ResetlowerscopelevelFlag(){ if(lowerscopelevelFlag == true){ lowerscopelevelFlag = false; } }

    //while identifer for condition evaluation
    bool GetwhileFlag() const { return whileIdentifierFlag; }
    void SetwhileFlag(){ whileIdentifierFlag = true; }
    void ResetwhileFlag(){ if(whileIdentifierFlag == true){ whileIdentifierFlag = false; } }

    //increment param_num for handling one or more parameters in a function
    int Getparam_num() const { return param_num; }
    void Incrementparam_num() { param_num++; }
    void Resetparam_num() { param_num = -1; }

    //scope level methods
    int GetscopeLevel() const { return scopeLevel; }
    void IncrementscopeLevel() { scopeLevel++; }
    void DecrementscopeLevel() { scopeLevel--; }

    //expression assignment boolean flag methods
    bool GetsecondcallFlag() const { return secondcallFlag; }
    void SetsecondcallFlag(){ secondcallFlag = true; }
    void ResetsecondcallFlag(){ if(secondcallFlag == true){ secondcallFlag = false; } }

    //expression assignment boolean flag methods
    bool GetexpressionassignFlag() const { return expressionassignFlag; }
    void SetexpressionassignFlag(){ expressionassignFlag = true; }
    void ResetexpressionassignFlag(){ if(expressionassignFlag == true){ expressionassignFlag = false; } }

    //identifer assign boolean methods
    bool GetidentifierassignFlag() const { return identifierassignFlag; }
    void SetidentifierassignFlag(){ identifierassignFlag = true; }
    void ResetidentifierassignFlag(){ if(identifierassignFlag == true){ identifierassignFlag = false; } }

    //equating variables boolean methods
    bool GetequatingvarFlag() const { return equatingvarFlag; }
    void SetequatingvarFlag(){ equatingvarFlag = true; }
    void ResetequatingvarFlag(){ if(equatingvarFlag == true){ equatingvarFlag = false; } }

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
    //To check: reset for ifelse counter needed?

    //whileLabelCounter methods
    int GetwhileLabelCounter() const { return whileLabelCounter; }
    void IncrementwhileLabelCounter() { whileLabelCounter++; }
    //To check: reset for while counter needed?

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
        auto it = VarMap.find(var);
        if (it != VarMap.end()) {
            return it->second; // Key exists, return mapped value
        }
        return ""; // Return an empty string or a default value
    }
    void MapRegister(const std::string& var, const std::string& Reg) {
        VarMap[var] = Reg;
    }
    void FreeRegister(const std::string& var){
        VarMap.erase(var);
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
