#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context& context) const
{
    if(context.GetassignFlag() == true){
        stream << value_;
    }
    else if(context.GetretFlag() == true){
        stream << "li a0, " << value_ << std::endl;
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
