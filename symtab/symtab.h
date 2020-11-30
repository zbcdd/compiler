#include <unordered_map>
#include <vector>
#include <string>

enum TYPE
{
    VOID_TYPE = 0, BOOL_TYPE, INT_TYPE, PTR_TYPE, ARR_TYPE, STRUCT_TYPE, FUNC_TYPE
};

class sym_info
{
public:
    sym_info() {};
}

class arr_info: public sym_info
{
private:
    TYPE type;
    int length;
public:
    arr_info() {};
    arr_info(TYPE type, int length): type(type), length(length) {};
    TYPE get_type();
    TYPE get_length();
}

class struct_info: public sym_info
{
private:
    std::vector<std::string> name_list;
    std::vector<symbol*> sym_list;
public:
    struct_info() {};
    void add_var(std::string, symbol*);
    std::vector<std::string>* get_name_list();
    std::vector<symbol*>* get_sym_list();
}

class func_info: public sym_info
{
private:
    TYPE type;  // 返回值类型
    std::vector<symbol*> param_list;  // 参数
public:
    func_info() {};
    func_info(TYPE type) : type(type){};
    void add_param(symbol*){};
    TYPE get_type();
    std::vector<symbol*>* get_param_list();
}

class symbol
{
private:
    TYPE type;
    int value;
    sym_info* info;  // arr_info struct_info func_info
    int pos;  // 存储位置
    int size;  // 大小
public:
    symbol(TYPE type) : type(type) {};
    symbol(TYPE type, int value) : type(type), value(value) {};
    symbol(TYPE type, int value, sym_info* info) : type(type), value(value), info(info) {};
    TYPE get_type();
    int get_value();
    sym_info* get_info();
    void set_pos(int pos);
    int get_pos();
    void set_size(int size);
    int get_size();
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
