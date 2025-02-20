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

%union{
  Node*				node;
  NodeList*			node_list;
  int          		number_int;
  double       		number_float;
  std::string*		string;
  TypeSpecifier 	type_specifier;
  yytokentype  		token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> translation_unit external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression declarator direct_declarator statement compound_statement jump_statement

%type <node> init_statement selection_statement parameter_declarator

%type <node_list> statement_list parameter_list

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <string> IDENTIFIER
%type <type_specifier> type_specifier declaration_specifiers


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
	: declaration_specifiers declarator compound_statement {
		$$ = new FunctionDefinition($1, NodePtr($2), NodePtr($3));
	}
	;

declaration_specifiers
	: type_specifier { $$ = $1; }
	;

type_specifier
	: INT {
		$$ = TypeSpecifier::INT;
	}
	;

init_statement
    : type_specifier IDENTIFIER {
        $$ = new VariableDefinition($1, NodePtr(new Identifier(std::move(*$2))));
        delete $2;
    }
    ;

parameter_list
    : init_statement  { $$ = new NodeList(NodePtr($1)); }
    | parameter_list ',' init_statement { $1->PushBack(NodePtr($3)); $$ = $1; }
    ;

declarator
	: direct_declarator { $$ = $1; }
	| parameter_declarator { $$ = $1; }
    ;

direct_declarator
    : IDENTIFIER '(' ')' {
		$$ = new DirectDeclarator(NodePtr(new Identifier(std::move(*$1))));
        delete $1;
	}
	;

parameter_declarator
    : IDENTIFIER '(' parameter_list ')' { $$ = new ParameterDeclarator(NodePtr(new Identifier(std::move(*$1))), NodePtr($3)); delete $1; }
    ;

compound_statement
	: '{' statement_list '}' { $$ = $2; }
	;

statement_list
	: statement { $$ = new NodeList(NodePtr($1)); }
	| statement_list statement { $1->PushBack(NodePtr($2)); $$=$1; }
	;

statement
	: jump_statement { $$ = $1; }
    | init_statement ';' { $$ = $1; }
    | expression ';' { $$ = $1; }
	| selection_statement
	;

jump_statement
	: RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement(NodePtr($2));
	}
	;

selection_statement
    : IF '(' expression ')' compound_statement {
        $$ = new IfStatement(NodePtr($3), NodePtr($5), nullptr);
    }
    | IF '(' expression ')' compound_statement ELSE compound_statement {
        $$ = new IfStatement(NodePtr($3), NodePtr($5), NodePtr($7));
    }
    ;


primary_expression
    : IDENTIFIER {
        $$ = new Identifier(std::move(*$1));
        delete $1;
	}
	| INT_CONSTANT {
		$$ = new IntConstant($1);
	}
	;

postfix_expression
	: primary_expression
	;

unary_expression
	: postfix_expression
	;

cast_expression
	: unary_expression
	;

multiplicative_expression
	: cast_expression
	;

additive_expression
	: multiplicative_expression
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
	: logical_or_expression
	;

assignment_expression
	: conditional_expression
    | IDENTIFIER '=' INT_CONSTANT {
        $$ = new AssignmentOperator(NodePtr(new IntConstant($3)),NodePtr(new Identifier(std::move(*$1))));
        delete $1;
    }
	;

expression
	: assignment_expression
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
