#include "../../include/context/ast_context.hpp"

namespace ast{

void ContextConstant::PrintConst(std::ostream &stream) const {
    switch(type_){
        case Type::_FLOAT:
            stream << assembler_directives.at(Type::_FLOAT) << " " << low_bits << std::endl;
            break;
            case Type::_DOUBLE:
            stream << assembler_directives.at(Type::_DOUBLE) << " " << low_bits << std::endl;
            stream << assembler_directives.at(Type::_DOUBLE) << " " << high_bits << std::endl;
            break;
        default:
            throw std::runtime_error("ContextConstant::PrintConst: Unsupported type");
    }
}

int Context::registerConstant(float value) {
    ContextConstant constant(value);
    constants.push_back(constant);
    return constantIndex++;
}

int Context::registerConstant(double value) {
    ContextConstant constant(value);
    constants.push_back(constant);
    return constantIndex++;
}

void Context::outputConstantDeclaration(std::ostream &stream) const {
    int i = 0;
    for (const auto &constant : constants) {
        stream << ".LC" << i++ << ":" << std::endl;
        constant.PrintConst(stream);
    }
}
}



