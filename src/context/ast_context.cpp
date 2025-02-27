#include "../../include/context/ast_context.hpp"

namespace ast{

Context::Context()
{
    label_counter = 0;
    current_stack_offset = 0;
    mode_push(Mode::GLOBAL);
}

Context::~Context()
{
}

}//namespace ast
