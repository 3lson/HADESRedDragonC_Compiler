#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ast_direct_declarator.hpp"
#include "ast_node.hpp"

#include "context/ast_context.hpp"

#include "control_flow/ast_ifelse.hpp"
#include "control_flow/ast_while.hpp"

#include "functions/ast_function_definition.hpp"
#include "functions/ast_jump_statement.hpp"
#include "functions/ast_parameter_declarator.hpp"
#include "functions/ast_param_list.hpp"

#include "operations/ast_arithmetic_operator.hpp"
#include "operations/ast_unary.hpp"

#include "statements/ast_assignment_operator.hpp"
#include "statements/ast_variable_definition.hpp"
#include "statements/ast_compound_statements.hpp"

#include "symbols/ast_identifier.hpp"
#include "symbols/ast_constant.hpp"

#include "types/ast_type_specifier.hpp"

ast::NodePtr ParseAST(std::string file_name);
