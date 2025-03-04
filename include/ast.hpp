#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "functions/ast_function_definition.hpp"
#include "functions/ast_parameter_definition.hpp"

#include "operations/ast_arithmetic_operation.hpp"
#include "operations/ast_relational_operation.hpp"
#include "operations/ast_equality.hpp"
#include "operations/ast_bitwise_operation.hpp"
#include "operations/ast_logical_operation.hpp"
#include "operations/ast_unary_operation.hpp"
#include "operations/ast_operand.hpp"

#include "statements/ast_return.hpp"
#include "statements/ast_statements.hpp"
#include "statements/ast_declaration.hpp"
#include "statements/ast_assignment.hpp"

#include "symbols/ast_identifier.hpp"
#include "symbols/ast_constant.hpp"

#include "control_flow/ast_ifelse.hpp"
#include "control_flow/ast_while.hpp"

#include "types/ast_type_specifier.hpp"

#include "ast_direct_declarator.hpp"
#include "ast_node.hpp"

#include "context/ast_context.hpp"

ast::NodePtr ParseAST(std::string file_name);

#endif
