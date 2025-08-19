#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_return_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "operators/ast_binary_operator.hpp"
#include "operators/ast_logic_operator.hpp"
#include "operators/ast_conditional_operator.hpp"
#include "ast/ast_root.hpp"
#include "variables/ast_init_declarator.hpp"
#include "variables/ast_assignment_expression.hpp"
#include "variables/ast_declaration.hpp"
#include "variables/ast_array_declarator.hpp"
#include "ast_parameter_declaration.hpp"
#include "ast_if_statement.hpp"
#include "ast_if_else_statement.hpp"
#include "ast_while_statement.hpp"
#include "ast_for_statement.hpp"
#include "ast_function_call.hpp"
#include "ast_argument_expression.hpp"
#include "ast_switch_statement.hpp"
#include "ast_case_statement.hpp"
#include "ast_break_statement.hpp"

ast::NodePtr ParseAST(std::string file_name);
