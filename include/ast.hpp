#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "operators/ast_binary_operator.hpp"

ast::NodePtr ParseAST(std::string file_name);
