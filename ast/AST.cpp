#include <iostream>
#include <cstring>
#include <stdbool.h>
#include "AST.h"

using namespace std;

ASTNode::ASTNode() {};
ASTNode::ASTNode(NodeType nodeType): nodeType(nodeType) {}
ASTNode::ASTNode(NodeType nodeType, string msg): nodeType(nodeType), msg(msg) {}
ASTNode::ASTNode(NodeType nodeType, string msg, int idx, string name): nodeType(nodeType), msg(msg), idx(idx), name(name) {};
ASTNode::ASTNode(NodeType nodeType, string msg, int idx): nodeType(nodeType), msg(msg), idx(idx) {}

void ASTNode::addChild(ASTNode* child)
{
    children.push_back(child);
}

void ASTNode::setIdx(int idx)
{
    this -> idx = idx;
}

void ASTNode::setName(string name)
{
    this -> name = name;
}

void ASTNode::printTree(ASTNode* root, int layer, bool end, string end_info)
{
    // 特殊符号: ┗━━┣━━┃
    vector<ASTNode*> children = root -> children;
    for (int i = 0; i < layer; i ++){
        if (end_info[i] == '0') printf("┃\t");
        else printf("\t");
    }
    if (end) {
        printf("┗━━%s:%d\t%s\n", (this -> msg).c_str(), this -> idx, (this -> name).c_str());
    } else {
        printf("┣━━%s:%d\t%s\n", (this -> msg).c_str(), this -> idx, (this -> name).c_str());
    }
    for (int i = 0; i < children.size(); i ++) {
        ASTNode* child = children[i];
        bool nextend = (i == children.size() - 1);
        string next_end_info;
        if (end) next_end_info = end_info + "1";
        else next_end_info = end_info + "0";
        child -> printTree(child, layer + 1, nextend, next_end_info);
    }
}
