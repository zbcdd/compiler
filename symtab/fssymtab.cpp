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

int struct_node::add_var(string name)
{
    if ((this->si_map).count(name))
        return -1;
    (this->si_map)[name] = this->cur_idx++;
    return 1;
}

int struct_node::get_var(string name)
{
    if ((this->si_map).count(name))
        return (this->si_map)[name];
    return -1;
}

int struct_symtab::add_struct(string name, struct_node* node)
{
    if ((this->struct_tab).count(name))
        return -1;
    (this->struct_tab)[name] = node;
    return 1;
}

struct_node* struct_symtab::get_struct(string name)
{
    if ((this->struct_tab).count(name))
        return (this->struct_tab)[name];
    return NULL;
}

int struct_node::get_size()
{
    return this->cur_idx;
};

void struct_node::print()
{
    for (auto iter = (this->si_map).begin(); iter != (this->si_map).end(); iter++) {
        printf("%s, %d\n", iter->first.c_str(), iter->second);
    }
}

void struct_symtab::print()
{
    for (auto iter = (this->struct_tab).begin(); iter != (this->struct_tab).end(); iter++) {
        printf("%s:\n", (iter->first).c_str());
        iter->second->print();
    }
}