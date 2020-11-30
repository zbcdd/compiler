#include <unordered_map>
#include <vector>
#include <string>

enum TYPE
{
    VOID_TYPE = 0, BOOL_TYPE, INT_TYPE, PTR_TYPE, ARR_TYPE, STRUCT_TYPE, FUNC_TYPE
};

class symbol
{
public:
    TYPE type;
    int value;
    symbol(TYPE type) : type(type) {};
    symbol(TYPE type, int value) : type(type), value(value) {};
};

class symtab_list
{
private:
    std::vector<std::unordered_map<std::string, symbol*>* > list;
    void print_symtab(int idx, std::unordered_map<std::string, symbol*>* cur_symtab);
public:
    void init_list();
    void push_symtab();
    void pop_symtab();
    int insert_symbol(std::string, symbol*);
    symbol* find_symbol(std::string);
    void print_cur_symtab();
    void print_symtab_list();
};
