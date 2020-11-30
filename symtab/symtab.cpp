#include "symtab.h"
#include <cstdio>
#include <cstring>

void symtab_list::init_list()
{
    push_symtab();
}

void symtab_list::push_symtab()
{
    (this -> list).push_back(new std::unordered_map<std::string, symbol*>);
}

void symtab_list::pop_symtab()
{   
    if ((this -> list).size() == 0)
    {
        printf("no symtab to pop!\n");
        return;
    }
    std::unordered_map<std::string, symbol*>* cur_symtab = (this -> list).back();
    (this -> list).pop_back();
    (*cur_symtab).clear();
    delete(cur_symtab);
}

int symtab_list::insert_symbol(std::string name, symbol* sym)
{
    std::unordered_map<std::string, symbol*>* cur_symtab = (this -> list).back();
    if (cur_symtab -> count(name) != 0) 
        return 0;  // 重复定义
    (*cur_symtab)[name] = sym; 
    return 1;  // 可以添加
}

symbol* symtab_list::find_symbol(std::string name)
{
    for (auto iter = (this -> list).rbegin(); iter != (this -> list).rend(); iter ++)
    {
        std::unordered_map<std::string, symbol*>* cur_symtab = *iter;
        if ((*cur_symtab).count(name) != 0)
            return (*cur_symtab)[name];
    }
    return NULL;  // 没找到,访问没有声明的函数或变量
}

void symtab_list::print_symtab(int idx, std::unordered_map<std::string, symbol*>* cur_symtab)
{
    printf("symtab_list: NO.%d:\n", idx);
    for (auto iter = (*cur_symtab).begin(); iter != (*cur_symtab).end(); iter ++)
    { 
        printf("name: %s type: %d value: %d\n", (iter -> first).c_str(), iter -> second -> type, iter -> second -> value);
    }
}

void symtab_list::print_cur_symtab()
{
    int idx = (this -> list).size() - 1;
    this -> print_symtab(idx, (this -> list).back());
}

void symtab_list::print_symtab_list()
{
    for (int i = 0; i < (this -> list).size(); i ++)
    {
       this -> print_symtab(i, (this -> list)[i]);
    }
}

/*int main()
{
    symtab_list *s_l = new symtab_list();
    s_l -> init_list();
    s_l -> push_symtab();
    s_l -> pop_symtab();
    s_l -> insert_symbol("aa", new symbol(INT_TYPE, 20));
    s_l -> insert_symbol("aa", new symbol(INT_TYPE, 25));
    s_l -> insert_symbol("xx", new symbol(INT_TYPE, 28));
    symbol* ret = s_l -> find_symbol("xxx");
    printf("####\n");
    if (!ret) printf("xx not found!\n");
    ret = s_l -> find_symbol("aa");
    printf("aa: %d\n", ret -> value);
    s_l -> push_symtab();
    s_l -> insert_symbol("aa", new symbol(INT_TYPE, 30));
    s_l -> find_symbol("aa");
    s_l -> print_cur_symtab();
    s_l -> print_symtab_list();
    return 0;
}*/
