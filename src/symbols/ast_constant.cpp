#include "../../include/symbols/ast_constant.hpp"
namespace ast{

void IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string passed_reg) const
{
    (void)context;
    stream << "li " << passed_reg << ", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

}
