// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires {
	#include "ast.hpp"
	using namespace ast;

	extern int yylineno;
	extern char* yytext;
	extern Node* g_root;
	extern FILE* yyin;

	int yylex(void);
	void yyerror(const char*);
	int yylex_destroy(void);
}

%define parse.error detailed
%define parse.lac full

%union {
  Node*        	node;
  NodeList*    	node_list;
  int          	number_int;
  double       	number_float;
  std::string* 	string;
  TypeSpecifier	type_specifier;
  yytokentype  	token;
}

%token <string>    IDENTIFIER       /* std::string* */
%token <number_int>INT_CONSTANT     /* int          */
%token <number_float>FLOAT_CONSTANT /* double       */
%token <string>    STRING_LITERAL   /* std::string* */


%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token UNKNOWN

%type <node>       compound_statement
%type <node>       jump_statement

%type <node> translation_unit external_declaration function_definition
%type <node> primary_expression postfix_expression unary_expression cast_expression
%type <node> multiplicative_expression additive_expression shift_expression
%type <node> relational_expression equality_expression and_expression
%type <node> exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression
%type <node> declaration
%type <node> declarator direct_declarator init_declarator
%type <node> statement
%type <node_list> statement_list declaration_list
%type <type_specifier> type_specifier declaration_specifiers


%start ROOT
%%

/*--- Top-level and function definitions ---*/
ROOT
  : translation_unit               { g_root = $1; }
;

translation_unit
  : external_declaration           { $$ = $1; }
  | translation_unit external_declaration
;

external_declaration
  : function_definition            { $$ = $1; }
//   | declaration                    { $$ = new DeclarationStatement(NodePtr($1)); } /* NEW: allow globals */
;

function_definition
  : declaration_specifiers declarator compound_statement
      { $$ = new FunctionDefinition($1, NodePtr($2), NodePtr($3)); }
;

/*--- Expressions and constants (unchanged except assignment) ---*/
primary_expression
	: INT_CONSTANT {
		$$ = new IntConstant($1);
	}
	;

postfix_expression
  : primary_expression            { $$ = $1; }
;

unary_expression
  : postfix_expression            { $$ = $1; }
;

cast_expression
  : unary_expression              { $$ = $1; }
;

multiplicative_expression
  : cast_expression               { $$ = $1; }
  | multiplicative_expression '*' cast_expression
      { $$ = new BinaryOperator(BinOp::Mul, NodePtr($1), NodePtr($3)); }
  | multiplicative_expression '/' cast_expression
      { $$ = new BinaryOperator(BinOp::Div, NodePtr($1), NodePtr($3)); }
;

additive_expression
  : multiplicative_expression     { $$ = $1; }
  | additive_expression '+' multiplicative_expression
      { $$ = new BinaryOperator(BinOp::Add, NodePtr($1), NodePtr($3)); }
  | additive_expression '-' multiplicative_expression
      { $$ = new BinaryOperator(BinOp::Sub, NodePtr($1), NodePtr($3)); }
;

shift_expression
  : additive_expression
  ;

relational_expression
  : shift_expression
  ;

equality_expression
  : relational_expression
  ;

and_expression
  : equality_expression
  ;

exclusive_or_expression
  : and_expression
  ;

inclusive_or_expression
  : exclusive_or_expression
  ;

logical_and_expression
  : inclusive_or_expression
  ;

logical_or_expression
  : logical_and_expression
  ;

conditional_expression
  : logical_or_expression          { $$ = $1; }
  ;

/*--- NEW: assignment_expression to support '=' ---*/
assignment_expression
  : conditional_expression         { $$ = $1; }
//   | unary_expression '=' assignment_expression
//       { $$ = new BinaryOperator(BinOp::Assign, NodePtr($1), NodePtr($3)); } /* NEW */
;


expression
  : assignment_expression          { $$ = $1; }
  | expression ',' assignment_expression
    //   { /* sequence expr: you can chain or wrap in SequenceNode */ }
;

constant_expression
  : conditional_expression         { $$ = $1; }
;

/*--- NEW: declaration and init-declarator rules ---*/
declaration
  : declaration_specifiers ';'                                                   { $$ = new Declaration(NodePtr($1), {}); }
//   | declaration_specifiers init_declarator_list ';'
//       { $$ = new Declaration(NodePtr($1), *$2); delete $2; } /* NEW */
;

declaration_specifiers
  : type_specifier                                                                           { $$ = $1; }
;

type_specifier
	: INT { $$ = TypeSpecifier::INT; }
	// | VOID
	// | CHAR
	// | SHORT
	// | LONG
	// | FLOAT
	// | DOUBLE
	// | SIGNED
	// | UNSIGNED
	// | struct_specifier
	// | enum_specifier
	// | TYPE_NAME
	;


init_declarator_list
  : init_declarator                                                              // { $$ = new NodeList(NodePtr($1)); } /* NEW */
//   | init_declarator_list ',' init_declarator
//       { $1->PushBack(NodePtr($3)); $$ = $1; }
;

init_declarator
  : declarator                                                                    { $$ = $1; }
//   | declarator '=' initializer
//       { $$ = new InitDeclarator(NodePtr($1), NodePtr($3)); } /* NEW */
;

// initializer
//   : assignment_expression                                                         { $$ = $1; } /* NEW */
//   | '{' initializer_list '}'                                                       { /* for aggregates later */ }
// ;

/*--- Statements, including declarations and expressions ---*/
// expression_statement
//   : ';'                                                                            { $$ = new EmptyStatement(); } /* NEW */
//   | expression ';'                                                                 { $$ = new ExpressionStatement(NodePtr($1)); } /* NEW */
// ;

statement
  : compound_statement                                                             { $$ = $1; }
  | jump_statement                                                                 { $$ = $1; }
//   | labeled_statement                                                              { $$ = $1; }
//   | expression_statement                                                           { $$ = $1; }
//   | declaration                                                                    { $$ = new DeclarationStatement(NodePtr($1)); } /* NEW */
//   | selection_statement                                                            { $$ = $1; }
//   | iteration_statement                                                            { $$ = $1; }
;

compound_statement
  : '{' statement_list '}'                                                         { $$ = $2; }
;

declaration_list
  : declaration                                                                    { $$ = new NodeList(NodePtr($1)); }
  | declaration_list declaration                                                   { $1->PushBack(NodePtr($2)); $$ = $1; }
;


declarator
	: direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER {
		$$ = new Identifier(std::move(*$1));
		delete $1;
	}
	| direct_declarator '(' ')' {
		$$ = new DirectDeclarator(NodePtr($1));
	}
	;

statement_list
  : statement                                                                      { $$ = new NodeList(NodePtr($1)); }
  | statement_list statement                                                        { $1->PushBack(NodePtr($2)); $$ = $1; }
;



// selection_statement
//   : IF '(' expression ')' statement                                               { $$ = new IfStatement(NodePtr($3), NodePtr($5)); }
//   | IF '(' expression ')' statement ELSE statement                                 { $$ = new IfElseStatement(NodePtr($3), NodePtr($5), NodePtr($7)); }
// ;

// iteration_statement
//   : WHILE '(' expression ')' statement                                             { $$ = new WhileStatement(NodePtr($3), NodePtr($5)); }
//   | FOR '(' expression_statement expression_statement ')' statement                 { /* etc. */ }
// ;

jump_statement
  : RETURN ';'                                                                     { $$ = new ReturnStatement(nullptr); }
  | RETURN expression ';'                                                          { $$ = new ReturnStatement(NodePtr($2)); }
;

%%

void yyerror (const char *s)
{
  std::cerr << "Error: " << s << " at line " << yylineno;
  std::cerr << " near '" << yytext << "'" << std::endl;
  std::exit(1);
}

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if (!yyin) {
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    std::exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return NodePtr(g_root);
}
