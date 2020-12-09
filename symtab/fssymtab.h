#include <unordered_set>
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

class struct_symtab
{
private:
public:
};