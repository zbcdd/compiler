%{
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"./intercode/intercode.h"

#define ID_DEC "ID Declaration"
#define CONST_DEC "Const Declaration"
#define EXPR_DEC "Expr"

extern int yylex();
extern FILE * yyin;
extern int yylineno;
void yyerror(const char *str);
int idx = 0;
symtab_list* list_ptr;
ASTNode* ASTroot;
InterCodeList ic_list = InterCodeList();
%}
%union {
    ASTNode* node;
    char* str;
}
%token<str> IDENTIFIER CONSTANT
%token<node> PTR_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token<node> AND_OP OR_OP
%token<node> INT VOID
%token<node> STRUCT
%token<node> IF ELSE WHILE DO FOR CONTINUE BREAK RETURN
%token<node> CIN COUT

%start translation_unit


%type<node> primary_expression postfix_expression input_expression direct_input_expression
%type<node> output_expression direct_output_expression argument_expression_list pow_expression
%type<node> multiplicative_expression additive_expression relational_expression equality_expression 
%type<node> logical_and_expression logical_or_expression assignment_expression expression declaration 
%type<node> init_declarator_list init_declarator type_specifier struct_or_union_specifier 
%type<node> struct_declaration_list struct_declaration struct_declarator_list declarator direct_declarator 
%type<node> parameter_list parameter_declaration identifier_list initializer initializer_list 
%type<node> statement compound_statement block_item_list block_item expression_statement 
%type<node> selection_statement iteration_statement jump_statement translation_unit external_declaration 
%type<node> function_definition
%type<node> enter_scope


%locations
%define parse.error verbose

%%

primary_expression
	: IDENTIFIER {
        $$ = new ASTNode(NodeType::ID, ID_DEC, idx ++, $1);
    }
	| CONSTANT {
        $$ = new ASTNode(NodeType::CONST, CONST_DEC, idx ++, $1);
    }
	| '(' expression ')' {
        $$ = $2;
    }
	;

postfix_expression
	: primary_expression {
        $$ = $1;
    }
	| postfix_expression '[' expression ']' {
        $$ = new ASTNode(NodeType::EXPR, EXPR_DEC, idx ++, "get_value_op:[]");
        $$ -> addChild($1);  $$ -> addChild($3);
    }
	| postfix_expression '(' ')' {
        $$ = new ASTNode(NodeType::FUNC_CALL, "Funcation Call", idx ++, "no param");
        $$ -> addChild($1);
    }
	| postfix_expression '(' argument_expression_list ')'{
        $$ = new ASTNode(NodeType::FUNC_CALL, "Functaion Call", idx ++, "have params");
        $$ -> addChild($1); $$ -> addChild($3);
    }
	| postfix_expression '.' IDENTIFIER {
        $$ = new ASTNode(NodeType::EXPR, "Struct Use", idx ++, "get_value_op:." );
        $$ -> addChild($1); $$ -> addChild(new ASTNode(NodeType::ID, ID_DEC, idx ++, $3));
    }
	| postfix_expression PTR_OP IDENTIFIER
    | '!' primary_expression {
        $$ = new ASTNode(NodeType::EXPR, "Logical not expression", idx ++, "unary_op:!");
        $$ -> addChild($2);
    }
	;

input_expression
    : CIN direct_input_expression {
        $$ = $2;
    }
    ;

direct_input_expression
    : RIGHT_OP postfix_expression {
        $$ = new ASTNode(NodeType::EXPR, "Input Expression", idx ++);
        $$ -> addChild($2);
    }
    | direct_input_expression RIGHT_OP postfix_expression {
        $$ = $1;
        $$ -> addChild($3);
    }
    ;

output_expression
    : COUT direct_output_expression {
        $$ = $2;
    }
    ;

direct_output_expression
    : LEFT_OP postfix_expression {
        $$ = new ASTNode(NodeType::EXPR, "Output Expression", idx ++);
        $$ -> addChild($2);
    }
    | direct_output_expression LEFT_OP postfix_expression {
        $$ = $1;
        $$ -> addChild($3);
    }
    ;

argument_expression_list
	: assignment_expression {
        $$ = new ASTNode(NodeType::EXPR, "Argument List", idx ++);
        $$ -> addChild($1);
    }
	| argument_expression_list ',' assignment_expression {
        $$ = $1;
        $$ -> addChild($3);
    }
	;

pow_expression
    : postfix_expression {
        $$ = $1;
    }
    | pow_expression '^' postfix_expression {
        if ($1 -> name != "^") {
            $$ = new ASTNode(NodeType::EXPR, "Pow Expression", idx ++, "arithmetic_op:^");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
    ;

multiplicative_expression
	: pow_expression {
        $$ = $1;
    }
	| multiplicative_expression '*' pow_expression {
        if ($1 -> msg != "Multiplicative Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:*");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:*");
            $$ -> addChild($1); $$ -> addChild($3);
        }
    }
	| multiplicative_expression '/' pow_expression {
        if ($1 -> msg != "Multiplicative Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:/");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:/");
            $$ -> addChild($1); $$ -> addChild($3);
        }
    }
	| multiplicative_expression '%' pow_expression {
        if ($1 -> msg != "Multiplicative Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:%");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = new ASTNode(NodeType::EXPR, "Multiplicative Expression", idx ++, "arithmetic_op:%");
            $$ -> addChild($1); $$ -> addChild($3);
        }
    }
	;

additive_expression
	: multiplicative_expression {
        $$ = $1;
    }
	| additive_expression '+' multiplicative_expression {
        if ($1 -> msg != "Additive Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Additive Expression", idx ++, "arithmetic_op:+");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = new ASTNode(NodeType::EXPR, "Additive Expression", idx ++, "arithmetic_op:+");
            $$ -> addChild($1); $$ -> addChild($3);
        }
    }
	| additive_expression '-' multiplicative_expression {
        if ($1 -> msg != "Additive Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Additive Expression", idx ++, "arithmetic_op:-");
            $$ -> addChild($1); $$ -> addChild($3);
       } else {
            $$ = new ASTNode(NodeType::EXPR, "Additive Expression", idx ++, "arithmetic_op:-");
            $$ -> addChild($1); $$ -> addChild($3);
        }
    }
	;

relational_expression
	: additive_expression {
        $$ = $1;
    }
	| relational_expression '<' additive_expression {
        if ($1 -> msg != "Relational Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Relational Expression", idx ++, "relational_op:<");
            $$ -> addChild($1); $$ -> addChild($3);
       } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	| relational_expression '>' additive_expression {
        if ($1 -> msg != "Relational Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Relational Expression", idx ++, "relational_op:>");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	| relational_expression LE_OP additive_expression {
        if ($1 -> msg != "Relational Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Relational Expression", idx ++, "relational_op:<");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	| relational_expression GE_OP additive_expression {
        if ($1 -> msg != "Relational Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Relational Expression", idx ++, "relational_op:<");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	;

equality_expression
	: relational_expression {
        $$ = $1;
    }
	| equality_expression EQ_OP relational_expression {
        if ($1 -> msg != "Equality Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Equality Expression", idx ++, "equality_op:==");
            $$ -> addChild($1); $$ -> addChild($3);
       } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	| equality_expression NE_OP relational_expression {
        if ($1 -> msg != "Equality Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Equality Expression", idx ++, "equality_op:!=");
            $$ -> addChild($1); $$ -> addChild($3);
       } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	;

logical_and_expression
	: equality_expression {
        $$ = $1;
    }
	| logical_and_expression AND_OP equality_expression {
        if ($1 -> msg != "Logical AND Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Logical AND Expression", idx ++, "logical_op:&&");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	;

logical_or_expression
	: logical_and_expression {
        $$ = $1;
    }
	| logical_or_expression OR_OP logical_and_expression {
        if ($1 -> msg != "Logical OR Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Logical OR Expression", idx ++, "logical_op:||");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	;

assignment_expression
	: logical_or_expression {
        $$ = $1;
    }
	| postfix_expression '=' assignment_expression {
        if ($1 -> msg != "Assignment Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Assignment Expression", idx ++, "assign_op:=");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
	;

expression
	: assignment_expression {
        $$ = $1;
    }
	| expression ',' assignment_expression {
        if ($1 -> msg == "Input Expression" || $1 -> msg == "Output Expression") {
            yyerror("Error using comma after input / output statement");
            exit(1);
        }
        if ($1 -> msg != "Comma Expression") {
            $$ = new ASTNode(NodeType::EXPR, "Comma Expression", idx ++, "op:,");
            $$ -> addChild($1); $$ -> addChild($3);
        } else {
            $$ = $1;
            $$ -> addChild($3);
        }
    }
    /* | input_expression {
        $$ = $1;
    }
    | output_expression {
        $$ = $1;
    } */
	;

declaration
	: type_specifier ';'{
        $$ = $1;
    }
	| type_specifier init_declarator_list ';' {
        $$ = new ASTNode(NodeType::VAR_DECLARATION, "Var Declaration", idx ++);
        $$ -> addChild($1); $$ -> addChild($2);
        std::vector<ASTNode*>* children = $2 -> getChildren();
        for (auto iter = children -> begin(); iter != children -> end(); iter ++) {
            ASTNode* cur_node = *iter;
            if (cur_node -> temp_symbol -> get_type() != TYPE::ARR_TYPE)
                cur_node -> temp_symbol -> set_type(TYPE::INT_TYPE);  // 不是arr这里就应该是int
            else {  // 是arr
                arr_info* cur_info = new arr_info();
                if ($1 -> name == "int")
                    cur_info -> set_type(TYPE::INT_TYPE);
                else
                    cur_info -> set_type(TYPE::STRUCT_TYPE);
                cur_node -> temp_symbol -> set_info(cur_info); 
            }
        }
    }
	;

init_declarator_list
	: init_declarator {
        $$ = new ASTNode(NodeType::INIT_LIST, "Initializer List", idx ++);
        $$ -> addChild($1);
    }
	| init_declarator_list ',' init_declarator {
        $$ = $1;
        $$ -> addChild($3);
    }
	;

init_declarator
	: declarator {
        if (list_ptr -> check_dup($1 -> name)) {  // 判重
            printf("重复 %s\n", ($1 -> name).c_str());
            yyerror("duplicate var declaration");
        }
        list_ptr -> insert_symbol($1 -> name, $1 -> temp_symbol);  // 转正了
        $$ = $1;
    }
	| declarator '=' initializer {
        if (list_ptr -> check_dup($1 -> name)) {  // 判重
            printf("重复 %s\n", ($1 -> name).c_str());
            yyerror("duplicate var declaration");
        }
        list_ptr -> insert_symbol($1 -> name, $1 -> temp_symbol);  // 转正了
        $$ = new ASTNode(NodeType::INIT, "Initializer", idx ++, "op:=");
        $$ -> addChild($1); $$ -> addChild($3);
        $$ -> temp_symbol = $1 -> temp_symbol;
    }
	;

type_specifier
	: VOID {
        $$ = new ASTNode(NodeType::TYPE_SPECIFIER, "Type Specifier", idx ++, "void");
    }
	| INT {
        $$ = new ASTNode(NodeType::TYPE_SPECIFIER, "Type Specifier", idx ++, "int");
    }
	| struct_or_union_specifier {
        $$ = $1;
    }
	;

struct_or_union_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' {
        $$ = new ASTNode(NodeType::TYPE_SPECIFIER, "Type Specifier", idx ++, "struct");
        $$ -> addChild($4);
    }
	| STRUCT '{' struct_declaration_list '}' {
        $$ = new ASTNode(NodeType::TYPE_SPECIFIER, "Type Specifier", idx ++, "struct");
        $$ -> addChild($3);
    }
	| STRUCT IDENTIFIER {
        $$ = new ASTNode(NodeType::TYPE_SPECIFIER, "Type Specifier", idx ++, "struct");
    }
	;

struct_declaration_list
	: struct_declaration {
        $$ = new ASTNode(NodeType::STRUCT_DEC_LIST, "Struct Declaration List", idx ++);
        $$ -> addChild($1);
    }
	| struct_declaration_list struct_declaration {
        $$ = $1;
        $$ -> addChild($2);
    }
	;

struct_declaration
	: type_specifier struct_declarator_list ';' {
        $$ = new ASTNode(NodeType::STRUCT_DECLARATION, "Struct Declaration", idx ++);
        $$ -> addChild($1); $$ -> addChild($2);
    }
	;

struct_declarator_list
	: declarator {
        $$ =  new ASTNode(NodeType::STRUCT_DEC_LIST, "Struct Declarator List", idx ++);
        $$ -> addChild($1);
    }
	| struct_declarator_list ',' declarator {
        $$ = $1;
        $$ -> addChild($3);
    }
	;

declarator
	: direct_declarator {
        $$ = $1;
    }
	;

direct_declarator
	: IDENTIFIER {
        $$ = new ASTNode(NodeType::VAR_DECLARATION, "Var Declaration", idx ++, $1);
        $$ -> temp_symbol = new symbol($1);
    }
	| '(' declarator ')' {
        $$ = $2;
    }
	| direct_declarator '[' assignment_expression ']' {
        $$ = new ASTNode(NodeType::ARR_DECLARATION, "Arr Declaration", idx ++, $1 -> name);
        $$ -> addChild($1); $$ -> addChild($3);
        $$ -> temp_symbol = $1 -> temp_symbol;
        $$ -> temp_symbol -> set_type(TYPE::ARR_TYPE);  // 数组
    }
    | direct_declarator '(' parameter_list ')' {
        $$ = new ASTNode(NodeType::PARAM_DECLARATION, "Function Declaration", idx ++);
        $$ -> addChild($1); $$ -> addChild($3);
        $$ -> temp_symbol = $1 -> temp_symbol;
        $$ -> temp_symbol -> set_type(TYPE::FUNC_TYPE);  // 函数
        func_info* cur = new func_info();
        // 将parameter_list里面的symbol加进来 (+++)
        $$ -> temp_symbol -> set_info(cur);
    }
	| direct_declarator '(' identifier_list ')' {
        $$ = new ASTNode(NodeType::VAR_DECLARATION, "Function Call", idx ++);
        $$ -> addChild($1); $$ -> addChild($3);
    }
	| direct_declarator '(' ')' {
        $$ = $1;
        $$ -> temp_symbol -> set_type(TYPE::FUNC_TYPE);  // 函数
        func_info* cur = new func_info();
        // 没有参数
        $$ -> temp_symbol -> set_info(cur);
    }
	;

parameter_list
	: parameter_declaration {
        $$ = new ASTNode(NodeType::PARAM_DECLARATION, "Parameter Declaration List", idx ++);
        $$ -> addChild($1);
    }
	| parameter_list ',' parameter_declaration {
        $$ = $1;
        $$ -> addChild($3);
    }
	;

parameter_declaration
	: type_specifier declarator {
        $$ = new ASTNode(NodeType::PARAM_DECLARATION, "Parameter Declaration", idx ++);
        $$ -> addChild($1); $$ -> addChild($2);
    }
	| type_specifier {
        $$ = new ASTNode(NodeType::PARAM_DECLARATION, "Parameter Declaration", idx ++);
        $$ -> addChild($1);
    }
	;

identifier_list
	: IDENTIFIER {
        $$ = new ASTNode(NodeType::ID, "Identifier List", idx ++);
        $$ -> addChild(new ASTNode(NodeType::ID, ID_DEC, idx ++, $1));
    }
	| identifier_list ',' IDENTIFIER {
        $$ = $1;
        $$ -> addChild(new ASTNode(NodeType::ID, ID_DEC, idx ++, $3));
    }
	;

initializer
	: assignment_expression {
        $$ = $1;
    }
	| '{' initializer_list '}'{
        $$ = $2;
    }
	;

initializer_list
	: initializer {
        $$ = new ASTNode(NodeType::INIT_LIST, "Initializer List", idx ++);
        $$ -> addChild($1);
    }
	| initializer_list ',' initializer {
        $$ = $1;
        $$ -> addChild($3);
    }
	;

statement
	: compound_statement {
        $$ = $1;
    }
	| expression_statement {
        $$ = $1;
    }
	| selection_statement {
        $$ = $1;
    }
	| iteration_statement {
        $$ = $1;
    }
	| jump_statement {
        $$ = $1;
    }
	;

compound_statement
	: '{' enter_scope '}' {
        $$ = new ASTNode(NodeType::COMPOUND_STMT, "Compound Statement", idx ++);
        list_ptr -> pop_symtab();  // 弹出符号表
        // printf("弹出符号表\n");
    }
	| '{' enter_scope block_item_list '}' {
        // list_ptr -> print_symtab_list();
        list_ptr -> pop_symtab();  // 弹出符号表
        // printf("弹出符号表(先打印再弹出)\n");
        if ($3 -> msg == "Block Item List") {
            $$ = $3;
            $$ -> msg = "Compound Statement";
        } else {
            $$ = new ASTNode(NodeType::COMPOUND_STMT, "Compound Statement", idx ++);
            $$ -> addChild($3);
        }
    }
	;

enter_scope
    : {
        list_ptr -> push_symtab();
    }

block_item_list
	: block_item {
        $$ = $1;
    }
	| block_item_list block_item {
        if ($1 -> msg != "Block Item List") {
            $$ = new ASTNode(NodeType::BLOCK_ITEM_LIST, "Block Item List", idx ++);
            $$ -> addChild($1); $$ -> addChild($2);
        } else {
            $$ = $1;
            $$ -> addChild($2);
        }
    }
	;

block_item
	: declaration {
        $$ = $1;
    }
	| statement {
        $$ = $1;
    }
	;

expression_statement
	: ';' {
        $$ = new ASTNode(NodeType::EXPR, "Empty Statement");
    }
	| expression ';' {
        $$ = $1;
    }
    | input_expression ';' {
        $$ = $1;
    }
    | output_expression ';' {
        $$ = $1;
    }
	;

selection_statement
	: IF '(' expression ')' statement {
        $$ = new ASTNode(NodeType::SELECT_STMT, "Selection Statement", idx ++);
        $$ -> addChild($3); $$ -> addChild($5);
        // $3 -> msg = "Condition";
        // $5 -> msg = "Statement if Condition is True";
    }
	| IF '(' expression ')' statement ELSE statement {
        $$ = new ASTNode(NodeType::SELECT_STMT, "Selection Statement", idx ++);
        $$ -> addChild($3); $$ -> addChild($5); $$ -> addChild($7);
        // $3 -> msg = "Condition";
        // $5 -> msg = "Statement if Condition is True";
        // $7 -> msg = "Statement if Condition is False";
    }
	;

iteration_statement
	: WHILE '(' expression ')' statement {
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "while");
        $$ -> addChild($3); $$ -> addChild($5);
    }
	| DO statement WHILE '(' expression ')' ';' {
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "do while");
        $$ -> addChild($2); $$ -> addChild($5);
    }
	| FOR '(' expression_statement expression_statement ')' statement {
        if ($3 -> msg == "Input Expression") yyerror("unexpected input statement");
        if ($3 -> msg == "Output Expression") yyerror("unexpected output statement");
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "for");
        $$ -> addChild($3); $$ -> addChild($4);
        $$ -> addChild(new ASTNode(NodeType::EXPR, "Empty Statement"));
        $$ -> addChild($6);
    }
	| FOR '(' expression_statement expression_statement expression ')' statement {
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "for");
        $$ -> addChild($3); $$ -> addChild($4); $$ -> addChild($5); $$ -> addChild($7);
    }
	/* | FOR '(' declaration expression_statement ')' statement {
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "for");
        $$ -> addChild($3); $$ -> addChild($4); 
        $$ -> addChild(new ASTNode(NodeType::EXPR, "Empty Statement"));
        $$ -> addChild($6);
    } */
	/* | FOR '(' declaration expression_statement expression ')' statement {
        $$ = new ASTNode(NodeType::REPEAT_STMT, "Repeat Statement", idx ++, "for");
        $$ -> addChild($3); $$ -> addChild($4); $$ -> addChild($5); $$ -> addChild($7);
    } */
	;

jump_statement
	: CONTINUE ';' {
        $$ = new ASTNode(NodeType::JUMP_STMT, "Jump Statement", idx ++, "continue");
    }
	| BREAK ';' {
        $$ = new ASTNode(NodeType::JUMP_STMT, "Jump Statement", idx ++, "break");
    }
	| RETURN ';' {
        $$ = new ASTNode(NodeType::JUMP_STMT, "Jump Statement", idx ++, "return");
    }
	| RETURN expression ';' {
        $$ = new ASTNode(NodeType::JUMP_STMT, "Jump Statement", idx ++, "return expr");
        $$ -> addChild($2);
        $2 -> msg = "Returned Expression";
    }
	;

translation_unit
	: external_declaration {
        $$ = new ASTNode(NodeType::PROGRAM, "Translation Unit", idx ++);
        $$ -> addChild($1);
        ASTroot = $$;
    }
	| translation_unit external_declaration {
        $$ = $1;
        $$ -> addChild($2);
        ASTroot = $$;
    }
	;

external_declaration
	: function_definition {
        $$ = $1;
    }
	| declaration {
        $$ = $1;
    }
	;

function_definition
	: type_specifier declarator compound_statement {
        $$ = new ASTNode(NodeType::FUNC_DEFINITION, "Function Definition", idx ++);
        $$ -> addChild($1); $$ -> addChild($2); $$ -> addChild($3);
    }
	;

/* declaration_list
	: declaration {
        $$ = new ASTNode(NodeType::FUNC_DEC_LIST, "Function Declaration List", idx ++);
        $$ -> addChild($1);
    }
	| declaration_list declaration {
        $$ -> addChild($2);
    }
	;*/

%%

extern char yytext[];
extern int column;

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: At line %d. %s\n", yylineno, s);
	exit(1);
}

int main(int argc, char* argv[])
{
    list_ptr = new symtab_list();
    list_ptr -> init_list();
    bool print_lexer = false;
    if (argc == 1) {
        printf("[ERROR]: Please specify the input file.\n");
    } else {
        FILE* input_file;
        for (int i = 1; i < argc; i ++) {
            if (*argv[i] != '-') {
                input_file = fopen(argv[i], "r");
            } else if (strcmp(argv[i], "-l")) {
                print_lexer = true;
            }
        }
        if (!input_file) {
            printf("[ERROR]: Input file name is invalid. Please check the file name\n");
            return -1;
        } else {
            yyin = input_file;
        }
    }
    do {
       int ret = yyparse();
       if (ret) printf("PARSER ERROR!!!");
    } while (!feof(yyin));
    ASTroot -> printTree(ASTroot, 0, false, "");
    ic_list.read(ASTroot);
    ic_list.printCodeList();
    // list_ptr -> print_symtab_list(); 未完成
    return 0;
}

