#include "../../include/context/ast_context.hpp"

namespace ast{

std::string Context::new_label(std::string label)
{
    return label + std::to_string(label_counter++);
}

}
