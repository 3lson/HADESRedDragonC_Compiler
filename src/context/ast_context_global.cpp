#include "../../include/context/ast_context.hpp"

namespace ast{

void Global::push_lower(uint32_t value){
    lowerValues.push_back(value);
}

void Global::push_upper(uint32_t value){
    upperValues.push_back(value);
}

void Global::print_global(std::ostream &stream) const
{
    Type type = get_type();

    for (size_t i = 0; i < lowerValues.size(); i++)
    {
        stream << "\t" << assembler_directives.at(type) << " " << lowerValues.at(i) << std::endl;

        if (type == Type::_DOUBLE)
        {
            stream << "\t" << assembler_directives.at(type) << " " << upperValues.at(i) << std::endl;
        }
    }

    size_t i = lowerValues.size();
    while (i < static_cast<size_t>(get_array_size()))
    {
        stream << "\t.zero " << types_size.at(type) << std::endl;
        i++;
    }
}

void Context::print_global(std::ostream &stream) const
{
    stream << "\t.data" << std::endl;

    for (const auto& global : globalMap)
    {
        stream << "\t.align " << types_mem_shift.at(global.second.get_type()) << std::endl;
        stream << "\t.type global_" << global.first << ", @object" << std::endl;
        stream << "\t.globl global_" << global.first << std::endl;

        stream << "global_" << global.first << ":" << std::endl;
        global.second.print_global(stream);
        stream << std::endl;
    }
}

}
