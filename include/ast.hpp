#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_assignment_operator.hpp"
#include "ast_variable_definition.hpp"
#include "ast_ifelse.hpp"
#include "ast_parameter_declarator.hpp"
#include "ast_arithmetic_operator.hpp"
#include "ast_unary.hpp"


ast::NodePtr ParseAST(std::string file_name);
