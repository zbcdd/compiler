#include "fssymtab.h"
using namespace std;

int func_symtab::check_func(string name, int cnt)
{
    string postfix = "_i";
    for (int i = 0; i < cnt; i ++)
        name += postfix;
    return (this -> func_set).count(name);
}

int func_symtab::add_func(string name, int cnt)
{
    if (this -> check_func(name, cnt))
        return 0;  // 添加失败，意味着重定义
    string postfix = "_i";
    for (int i = 0; i < cnt; i ++)
        name += postfix;
    (this -> func_set).insert(name);
    printf("add function %s\n", name.c_str());
    return 1;  // 添加成功
}