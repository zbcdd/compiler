#include <vector>
#include <string>
#include <stdbool.h>
#include "../symtab/symtab.h"

enum NodeType
{
    PROGRAM,
    EXPR,
    TYPE_SPECIFIER,
    ID,
    CONST,
    VAR_DECLARATION,
    ARR_DECLARATION,
    POINTER_DECLARATION,
    FUNC_DEFINITION,
    PARAM_DECLARATION,
    STRUCT_DECLARATION,
    FUNC_CALL,
    COMPOUND_STMT,
    SELECT_STMT,
    REPEAT_STMT,
    JUMP_STMT,
    STRUCT_DEC_LIST,
    FUNC_DEC_LIST,
    INIT_LIST,
    INIT,
    BLOCK_ITEM_LIST,
};

class ASTNode
{
private:
    NodeType nodeType;
    std::vector<ASTNode*> children;
    int idx;
public:
    std::string msg;
    std::string name;
    ASTNode();
    ASTNode(NodeType nodeType);
    ASTNode(NodeType nodeType, std::string msg);
    ASTNode(NodeType nodeType, std::string msg, int idx);
    ASTNode(NodeType nodeType, std::string msg, int idx, std::string name);
    void addChild(ASTNode* child);
    void setIdx(int idx);
    void setName(std::string name);
    void printTree(ASTNode* root, int layer, bool endOrFirst, std::string);
};
