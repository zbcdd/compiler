#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "../ast/AST.h"

enum ARGTYPE
{
    NULL_ARG = 0,       // null
    TEMP,               // temp
    VAR,                // var
    FUNC,               // FUNCTION
    ARG_CONSTANT,           // #
    ARR,                // arr
    LABEL,              // label
};

enum USAGE
{
    ORIGIN = 0,         // normal    
    ADDRESS,            // &
    CONTENT,            // *
};

enum OPTYPE
{
    NULL_TYPE = 0,      // null
    DOP_ADD,            // +
    DOP_MINUS,          // -
    DOP_MULIPLY,        // *
    DOP_DIVIDE,         // /
    DOP_MOD,            // %
    DOP_POW,            // ^
    DOP_ASSIGNMENT,     // =
    DOP_GETVALUE,       // []
    OP_READ,            // cin
    OP_PRINT,           // cout
    RELOP_L,            // >
    RELOP_S,            // <
    RELOP_EQUALS,       // ==
    RELOP_LOE,          // <=
    RELOP_SOE,          // >=
    JUMP_L,             // IF > GOTO
    JUMP_S,             // IF < GOTO
    JUMP_EQUALS,        // IF == GOTO
    JUMP_LOE,           // IF <= GOTO
    JUMP_SOE,           // IF >= GOTO
    FUNC_DEF,           // FUNCTION name
    FUNCTION_CALL,      // CALL name
    PARAM,              // PARAM
    ARG,                // ARG
    ARRAY_DECLARATION,  // DEC 
    OP_RETURN,          // RETURN
    STRUCT_DEFINITION,  // struct
};

std::string itos(int n);

class VarPair 
{
public:
    USAGE usage;
    ARGTYPE type;
    int index;
    std::string name;
    VarPair();
    VarPair(ARGTYPE type, int index);
    VarPair(ARGTYPE type, std::string name);
    VarPair(ARGTYPE type, int index, std::string name);
};

class InterCode 
{
private:
    int label;
    VarPair result;
    OPTYPE op;
    VarPair arg1;
    VarPair arg2;
    static std::string toString(VarPair arg);
public:
    InterCode();
    InterCode(VarPair arg, OPTYPE op, VarPair result);
    InterCode(VarPair arg1, VarPair arg2, OPTYPE op, VarPair result);
    void setLabel(int n);
    void setResult(VarPair result);
    void setOperator(OPTYPE op);
    void setArgFirst(VarPair arg1);
    void setArgSecond(VarPair arg2);
    std::string printCode();
};

class Varlistnode 
{
private:
    std::vector<VarPair> varlist;
    Varlistnode* father;
public:
    Varlistnode();
    Varlistnode(Varlistnode* father);
    void addVar(VarPair vp);
    VarPair findVar(std::string name);
    Varlistnode* getFather();
};

class InterCodeList
{
private:
    static int label_count;                 // counter for label
    static int temp_count;                  // counter for TEMP
    static int var_count;                   // counter for VAR
    static int arr_count;                   // counter for ARR
    std::vector<InterCode> list;
    void classify();
    void arithmetic(ASTNode* root, Varlistnode* vlist, VarPair temp_result);
public:
    InterCodeList();
    InterCodeList(InterCodeList* alist);
    int getListSize();
    void read(ASTNode* root, Varlistnode* vlist);
    void printCodeList();
};
