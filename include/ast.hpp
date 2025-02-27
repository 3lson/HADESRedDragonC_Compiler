#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "functions/ast_function_definition.hpp"

#include "statements/ast_return.hpp"
#include "statements/ast_statements.hpp"
#include "statements/ast_declaration.hpp"
#include "statements/ast_assignment.hpp"

#include "symbols/ast_identifier.hpp"
#include "symbols/ast_constant.hpp"

#include "control_flow/ast_ifelse.hpp"

#include "types/ast_type_specifier.hpp"


#include "ast_direct_declarator.hpp"
#include "ast_node.hpp"

#include "context/ast_context.hpp"

ast::NodePtr ParseAST(std::string file_name);

#endif
