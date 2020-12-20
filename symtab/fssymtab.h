#include <unordered_set>
#include <unordered_map>
#include <string>

class func_symtab
{
private:
    std::unordered_set<std::string> func_set;
public:
    func_symtab() {};
    int add_func(std::string, int);
    int check_func(std::string, int);
};

class struct_node
{
private:
    int cur_idx;
    std::unordered_map<std::string, int> si_map;
public:
    struct_node() {this -> cur_idx = 0;};
    int add_var(std::string name);
    int get_var(std::string name);
    void print();
};

class struct_symtab  // 全局的struct表
{
private:
    std::unordered_map<std::string, struct_node*> struct_tab;
public:
    struct_symtab() {};
    int add_struct(std::string, struct_node*);
    struct_node* get_struct(std::string);
    void print();
};