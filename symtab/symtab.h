#include <unordered_map>
#include <vector>
#include <string>
class ASTNode;
class symbol;
enum TYPE
{
    VOID_TYPE = 1, BOOL_TYPE, INT_TYPE, PTR_TYPE, ARR_TYPE, STRUCT_TYPE, FUNC_TYPE
};

class sym_info
{
public:
    sym_info() {};
};

class arr_info: public sym_info
{
private:
    TYPE type;  // INT_TYPE STRUCT_TYPE
    int length;
public:
    arr_info() {};
    arr_info(TYPE type, int length): type(type), length(length) {};
    void set_type(TYPE type) {this -> type = type;};
    TYPE get_type();
    void set_length(int length) {this -> length = length;};
    int get_length();
};

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
};

class func_info: public sym_info
{
private:
    TYPE type;  // 返回值类型
    std::vector<symbol*>* param_list;  // 参数
public:
    func_info() {};
    func_info(TYPE type) : type(type){};
    void add_param(symbol*);
    TYPE get_type();
    std::vector<symbol*>* get_param_list();
};

class symbol
{
private:
    TYPE type;  // INT_TYPE ARR_TYPE STRUCT_TYPE FUNC_TYPE
    int value;
    sym_info* info;  // arr_info struct_info func_info
    int pos;  // 存储位置
    int size;  // 大小
    std::string name;  // 符号名
public:
    ASTNode* ast_node;
    symbol() {};
    symbol(std::string name) : name(name) {};
    symbol(TYPE type) : type(type) {};
    symbol(TYPE type, int value) : type(type), value(value) {};
    symbol(TYPE type, int value, sym_info* info) : type(type), value(value), info(info) {};
    void set_name(std::string);
    std::string get_name();
    void set_type(TYPE type);
    TYPE get_type();
    void set_value(int value);
    int get_value();
    void set_info(sym_info* info);
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
    int check_dup(std::string);
    void print_cur_symtab();
    void print_symtab_list();
};
