// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
    #include "ast.hpp"

		using namespace ast;

    extern Node* g_root;
    extern FILE* yyin;
    int yylex(void);
    void yyerror(const char*);
	int yylex_destroy(void);
}

// Represents the value associated with any kind of AST node.
%union{
	Node*         node;
	NodeList*     node_list;
	int          number_int;
	float       number_float;
	double 		number_double;
	std::string* string;
	yytokentype  token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL DOUBLE_CONSTANT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> translation_unit external_declaration function_definition primary_expression postfix_expression argument_expression_list
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers init_declarator_list
%type <node> init_declarator type_specifier struct_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <node> struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_list parameter_declaration
%type <node> identifier_list type_name abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <node> compound_statement declaration_list expression_statement selection_statement iteration_statement jump_statement

%type <node_list> statement_list

%type <string> assignment_operator storage_class_specifier

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <number_double> DOUBLE_CONSTANT
%type <string> IDENTIFIER


%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = $1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition(NodePtr($1), NodePtr($2), NodePtr($3)); }
	;

declaration_specifiers
	: type_specifier { $$ = $1; }
	;

type_specifier
	: INT { $$ = new TypeSpecifier(Type::_INT); }
    | DOUBLE { $$ = new TypeSpecifier(Type::_DOUBLE); }
    | FLOAT { $$ = new TypeSpecifier(Type::_FLOAT); }
	| CHAR 		{ $$ = new TypeSpecifier(Type::_CHAR); }
	| UNSIGNED 	{ $$ = new TypeSpecifier(Type::_UNSIGNED_INT); }
	| SHORT 	{ $$ = new TypeSpecifier(Type::_SHORT); }
	;

declarator
	: direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER                { $$ = new Identifier($1); }
	| direct_declarator '(' ')' { $$ = new DirectDeclarator(NodePtr($1)); }
	| direct_declarator '(' parameter_list ')' { $$ = new DirectDeclarator(NodePtr($1), NodePtr($3)); }
	;

parameter_list
	: parameter_declaration            { $$ = new ParameterList(NodePtr($1)); }
	| parameter_list ',' parameter_declaration  {
		ParameterList *parameter_list = dynamic_cast<ParameterList *>($1);
		parameter_list->PushBack(NodePtr($3));
		$$ = $1;}
	;

parameter_declaration
	: declaration_specifiers declarator         { $$ = new ParameterDefinition(NodePtr($1), NodePtr($2)); }
	;

statement
	: compound_statement 	{ $$ = new CompoundStatement(NodePtr($1)); }
	| expression_statement 	{ $$ = $1; }
	| jump_statement 		{ $$ = $1; }
	| selection_statement	{ $$ = $1; }
	| iteration_statement   { $$ = $1; }
	;

compound_statement
	: '{' declaration_list '}' 					{ $$ = new CompoundStatement(NodePtr($2)); }
	| '{' declaration_list statement_list '}' 	{
		CompoundStatement *compound_statement = new CompoundStatement(NodePtr($2));
		compound_statement->PushBack(NodePtr($3));
		$$ = compound_statement;
		}
	| '{' statement_list '}' 					{ $$ = new CompoundStatement(NodePtr($2)); }
	| '{' '}' 									{ $$ = new CompoundStatement(nullptr); }

statement_list
	: statement                 { $$ = new StatementList(NodePtr($1)); }
	| statement_list statement  { $1->PushBack(NodePtr($2)); $$=$1; }
	;

jump_statement
	: RETURN ';'            { $$ = new ReturnStatement(nullptr); }
	| RETURN expression ';' { $$ = new ReturnStatement(NodePtr($2)); }
	;


selection_statement
    : IF '(' expression ')' compound_statement {
        $$ = new IfStatement(NodePtr($3), NodePtr($5), nullptr);
    }
    | IF '(' expression ')' compound_statement ELSE compound_statement {
        $$ = new IfStatement(NodePtr($3), NodePtr($5), NodePtr($7));
    }
    ;

iteration_statement
    : WHILE '(' expression ')' compound_statement { $$ = new WhileStatement(NodePtr($3), NodePtr($5)); }
	;

primary_expression
	: INT_CONSTANT 	{ $$ = new IntConstant($1); }
    | FLOAT_CONSTANT 	{ $$ = new FloatConstant($1); }
    | DOUBLE_CONSTANT 	{ $$ = new DoubleConstant($1); }
	| IDENTIFIER	{ $$ = new Identifier($1); }
	;

expression_statement
	: ';'			{ $$ = new NodeList(nullptr); }
	| expression ';' { $$ = $1; }
	;

postfix_expression
	: primary_expression
	| postfix_expression INC_OP { $$ = new UnaryExpression(UnaryOp::INC, NodePtr($1)); }
    | postfix_expression DEC_OP { $$ = new UnaryExpression(UnaryOp::DEC, NodePtr($1)); }
	;

argument_expression_list
	: assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression { $$ = new UnaryExpression(UnaryOp::INC, NodePtr($2)); }
    | DEC_OP unary_expression { $$ = new UnaryExpression(UnaryOp::DEC, NodePtr($2)); }
    | '+' cast_expression { $$ = new UnaryExpression(UnaryOp::PLUS, NodePtr($2)); }
	| '-' cast_expression { $$ = new UnaryExpression(UnaryOp::MINUS, NodePtr($2)); }
	| '~' cast_expression { $$ = new UnaryExpression(UnaryOp::BITWISE_NOT, NodePtr($2)); }
	| '!' cast_expression { $$ = new UnaryExpression(UnaryOp::LOGICAL_NOT, NodePtr($2)); }
	;

cast_expression
	: unary_expression
	;

multiplicative_expression
    : cast_expression
    | multiplicative_expression '*' cast_expression { $$ = new ArithExpression(ArithOp::MUL, NodePtr($1), NodePtr($3)); }
    | multiplicative_expression '/' cast_expression { $$ = new ArithExpression(ArithOp::DIV, NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '%' cast_expression { $$ = new ArithExpression(ArithOp::MOD, NodePtr($1), NodePtr($3)); }
    ;

additive_expression
    : multiplicative_expression
    | additive_expression '+' multiplicative_expression { $$ = new ArithExpression(ArithOp::ADD, NodePtr($1), NodePtr($3)); }
    | additive_expression '-' multiplicative_expression { $$ = new ArithExpression(ArithOp::SUB, NodePtr($1), NodePtr($3)); }
    ;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression { $$ = new BitwiseExpression(BitwiseOp::LEFT_SHIFT, NodePtr($1), NodePtr($3)); }
	| shift_expression RIGHT_OP additive_expression { $$ = new BitwiseExpression(BitwiseOp::RIGHT_SHIFT, NodePtr($1), NodePtr($3)); }
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{ $$ = new RelationExpression(RelationOp::LESS_THAN, NodePtr($1), NodePtr($3)); }
	| relational_expression '>' shift_expression	{ $$ = new RelationExpression(RelationOp::GREATER_THAN, NodePtr($1), NodePtr($3)); }
	| relational_expression LE_OP shift_expression	{ $$ = new RelationExpression(RelationOp::LESS_THAN_OR_EQUAL, NodePtr($1), NodePtr($3)); }
	| relational_expression GE_OP shift_expression	{ $$ = new RelationExpression(RelationOp::GREATER_THAN_OR_EQUAL, NodePtr($1), NodePtr($3)); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression { $$ = new EqualityExpression(EqualityOp::EQUAL, NodePtr($1), NodePtr($3)); }
    | equality_expression NE_OP relational_expression { $$ = new EqualityExpression(EqualityOp::NOT_EQUAL, NodePtr($1), NodePtr($3)); }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression { $$ = new BitwiseExpression(BitwiseOp::BITWISE_AND, NodePtr($1), NodePtr($3)); }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression { $$ = new BitwiseExpression(BitwiseOp::BITWISE_XOR, NodePtr($1), NodePtr($3)); }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new BitwiseExpression(BitwiseOp::BITWISE_OR, NodePtr($1), NodePtr($3)); }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new LogicalExpression(LogicalOp::LOGICAL_AND, NodePtr($1), NodePtr($3)); }
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression { $$ = new LogicalExpression(LogicalOp::LOGICAL_OR, NodePtr($1), NodePtr($3)); }
	;

conditional_expression
	: logical_or_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression	{ $$ = new Assignment(NodePtr($1), NodePtr($3)); }
	;

expression
	: assignment_expression
	;

declaration
	: declaration_specifiers init_declarator_list ';'	{ $$ = new Declaration(NodePtr($1), NodePtr($2)); }
	;

init_declarator_list
	: init_declarator							{ $$ = new NodeList(NodePtr($1)); }
	| init_declarator_list ',' init_declarator	{ NodeList *declarator_list = dynamic_cast<NodeList *>($1); declarator_list->PushBack(NodePtr($3)); $$ = declarator_list; }
	;

init_declarator
	: declarator
	| declarator '=' initializer	{ $$ = new Assignment(NodePtr($1), NodePtr($3)); }
	;

initializer
	: assignment_expression
	;

initializer_list
	: initializer						{ $$ = new NodeList(NodePtr($1)); }
	| initializer_list ',' initializer	{ $1->PushBack(NodePtr($3)); $$ = $1; }
	;

declaration_list
	: declaration					{ $$ = new DeclarationList(NodePtr($1)); }
	| declaration_list declaration	{
		DeclarationList *declaration_list = dynamic_cast<DeclarationList *>($1);
		declaration_list->PushBack(NodePtr($2));
		$$ = declaration_list;
	}
	;

%%

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return NodePtr(g_root);
}
