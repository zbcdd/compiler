#include "intercode.h"


std::string itos(int n)
{
    std::ostringstream ostr;
    ostr << n;
    std::string astr = ostr.str();
    return astr;
};

// class VarPair
VarPair::VarPair()
{
    this -> type = NULL_ARG;
    this -> index = -1;
    this -> name = "";
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, int index)
{
    this -> type = type;
    this -> index = index;
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, std::string name)
{
    this -> type = type;
    this -> name = name;
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, int index, std::string name)
{
    this -> type = type;
    this -> index = index;
    this -> name = name;
    this -> usage = ORIGIN;
};

// class InterCode
std::string InterCode::toString(VarPair arg)
{
    std::string p1, p2, p3;
    switch (arg.usage)
    {
        case ORIGIN:
        {
            p1 = "";
            break;
        }
        case ADDRESS:
        {
            p1 = "&";
            break;
        }
        case CONTENT:
        {
            p1 = "*";
            break;
        }
        default:
        {
            p1 = "";
            // Programming Error
            break;
        }
    }
    switch (arg.type)
    {
        case TEMP:
        {
            p2 = "temp";
            break;
        }
        case VAR:
        {
            p2 = "var";
            break;
        }
        case ARGTYPE::ARG_CONSTANT:
        {
            p2 = "#";
            break;
        }
        case ARR:
        {
            p2 = "array";
            break;
        }
        case FUNC:
        {
            p2 = arg.name;
            break;
        }
        default:
        {
            p2 = "";
            // Programming Error
            break;
        }
    }
    // printf("%d", arg.index);
    p3 = itos(arg.index);
    std::string ss = p1 + p2 + p3;
    // printf("(%s, %s, %s)\n", p1.c_str(), p2.c_str(), p3.c_str());
    return ss;
};

InterCode::InterCode()
{
    this -> label = -1;
    this -> result = VarPair();
    this -> op = NULL_TYPE;
    this -> arg1 = VarPair();
    this -> arg2 = VarPair();
};

InterCode::InterCode(VarPair arg, OPTYPE op, VarPair result)
{
    this -> label = -1;
    this -> result = result;
    this -> op = op;
    this -> arg1 = arg;
    this -> arg2 = VarPair();
};

InterCode::InterCode(VarPair arg1, VarPair arg2, OPTYPE op, VarPair result)
{
    this -> label = -1;
    this -> result = result;
    this -> op = op;
    this -> arg1 = arg1;
    this -> arg2 = arg2;
};

void InterCode::setLabel(int n)
{
    this -> label = n;
};

void InterCode::setResult(VarPair result)
{
    this -> result = result;
};

void InterCode::setOperator(OPTYPE op)
{
    this -> op = op;
};

void InterCode::setArgFirst(VarPair arg1)
{
    this -> arg1 = arg1;
};

void InterCode::setArgSecond(VarPair arg2)
{
    this -> arg2 = arg2;
};

std::string InterCode::printCode()
{
    std::string code = "";
    // to be completed
    switch (this -> op)
    {
        
        case DOP_ASSIGNMENT:
        {
            if (this -> arg2.type == NULL_ARG)
            {
                code += toString(this -> result);
                code += " := ";
                code += toString(this -> arg1);
                code += "\n";
            }
            else
            {
                code += toString(this -> arg1);
                code += " := ";
                code += toString(this -> arg2);
                code += "\n";
                code += toString(this -> result);
                code += " := ";
                code += toString(this -> arg1);
                code += "\n";
            }
            break;
        }
        case DOP_ADD:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " + ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_MINUS:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " - ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_MULIPLY:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " * ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_DIVIDE:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " / ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_GETVALUE:
        {
            code += toString(this -> result);
            code += " := &";
            code += toString(this -> arg1);
            code += " + ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case FUNC_DEF:
        {
            code += "FUNCTION ";
            code += toString(this -> result);
            code += ":\n";
            break;
        }
        case ARRAY_DECLARATION:
        {
            code += "DEC ";
            code += toString(this -> result);
            code += " ";
            code += toString(this -> arg1);
            code += "\n";
            break;
        }
        case NULL_ARG:
        {
            /* code */
            break;
        }
        default:
        {
            break;
        }
    }
    return code;
};

// class Varlistnode
Varlistnode::Varlistnode()
{
    this -> father = NULL;
};

Varlistnode::Varlistnode(Varlistnode* father)
{
    this -> father = father;
};

void Varlistnode::addVar(VarPair vp)
{
    this -> varlist.push_back(vp);
};

VarPair Varlistnode::findVar(std::string name)
{
    Varlistnode* temp = this;
    while (true)
    {
        std::vector<VarPair>* list = &(temp -> varlist);
        for (auto iter = list -> begin(); iter != list -> end(); iter ++)
        {
            // printf("%s\n", (iter -> name).c_str());
            if (name == iter -> name)
                return VarPair(iter -> type, iter -> index, iter -> name);
        }
        if (temp -> father != NULL)
            temp = temp -> father;
        else 
            break;
    }
    return VarPair();
};

Varlistnode* Varlistnode::getFather()
{
    return this -> father;
};

// class InterCodeList
int InterCodeList::label_count = 0;

int InterCodeList::temp_count = 0;
   
int InterCodeList::var_count = 0;  

int InterCodeList::arr_count = 0;

void InterCodeList::classify()
{
    // to be completed
};

void InterCodeList::arithmetic(ASTNode* root, Varlistnode* vlist, VarPair temp_result)
{
    ASTNode* left = (*(root->getChildren()))[0];
    ASTNode* right = (*(root->getChildren()))[1];
    VarPair left_value;
    VarPair right_value;
    OPTYPE op;
    if (root -> msg == "Assignment Expression")
    { 
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            // error: a constant value can't be a left value
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {

            }
        }
        else if (right -> msg == "Const Declaration")
        {
            right_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(right -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_ASSIGNMENT;
    }
    else if (root -> msg == "Additive Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            left_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(left -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            right_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(right -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (root -> name == "arithmetic_op:+")
            op = DOP_ADD;
        else
            op = DOP_MINUS;
    }
    else if (root -> msg == "Multiplicative Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            left_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(left -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            right_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(right -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (root -> name == "arithmetic_op:*")
            op = DOP_MULIPLY;
        else if (root -> name == "arithmetic_op:/")
            op = DOP_DIVIDE;
        else
            op = DOP_MOD;
        
    }
    else if (root -> msg == "Pow Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            left_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(left -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            right_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(right -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_POW;
        // to be completed
    }
    else if (root -> msg == "Expr")
    { 
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else
        {
            // error: not a correct type with "[]"
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            right_value = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi(right -> name.c_str()));
            (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_GETVALUE;
        VarPair size = VarPair(ARGTYPE::ARG_CONSTANT, 4);
        VarPair width = VarPair(TEMP, temp_count++);
        (this -> list).push_back(InterCode(size, DOP_ASSIGNMENT, width));
        (this -> list).push_back(InterCode(right_value, width, DOP_MULIPLY, width));
    }
    // else if (root -> msg == "other")
    // {

    // }
    else
    {
        // error: xxx can't be a right value
    }
    if (left -> msg == "Expr")
        left_value.usage = CONTENT;
    if (right -> msg == "Expr")
        right_value.usage = CONTENT;
    (this -> list).push_back(InterCode(left_value, right_value, op, temp_result));
};

InterCodeList::InterCodeList()
{
    // do nothing
};
InterCodeList::InterCodeList(InterCodeList* alist)
{
    // to be completed
};

int InterCodeList::getListSize()
{
    return this -> list.size();
};

void InterCodeList::read(ASTNode* root, Varlistnode* vlist)
{
    if (root -> msg == "Translation Unit") {
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            this -> read(*iter, vlist);
        }
    }
    else if (root -> msg == "Function Definition")
    {
        InterCode* temp = new InterCode();
        temp -> setOperator(FUNC_DEF);
        if ((*(root -> getChildren()))[1] -> msg == "Var Declaration")
        {
            temp -> setResult(VarPair(FUNC, (*(root -> getChildren()))[1] -> name));
            this -> read((*(root -> getChildren()))[2], vlist);
        }
        else if ((*(root -> getChildren()))[1] -> msg == "Function Declaration")
        {
            ASTNode* nodeptr = (*(root -> getChildren()))[1];
            temp -> setResult(VarPair(FUNC, (*(nodeptr -> getChildren()))[0] -> name));
            (this -> list).push_back(*temp);
            // this -> read((*(nodeptr -> getChildren()))[1], vlist);
            // to be completed
        }
    }
    else if (root -> msg == "Parameter Declaration List")
    {
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            // this -> read(*iter);
            // to be completed
        }
    }
    else if (root -> msg == "Parameter Declaration")
    {
        // to be completed
    }
    else if (root -> msg == "Compound Statement") 
    {
        Varlistnode* newlist = new Varlistnode(vlist);
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            this -> read(*iter, newlist);
        }
    }
    else if (root -> msg == "Var Declaration") 
    {
        if ((*(root -> getChildren()))[0] -> name == "int")
        {
            std::vector<ASTNode*>* vars = (*(root -> getChildren()))[1] -> getChildren();
            for (auto iter = vars -> begin(); iter != vars -> end(); iter ++)
            {
                if ((*iter) -> msg == "Var Declaration")
                {
                    vlist -> addVar(VarPair(VAR, var_count++, (*iter) -> name));
                }
                else if ((*iter) -> msg == "Arr Declaration")
                {
                    VarPair arr = VarPair(ARR, arr_count++, (*iter) -> name);
                    vlist -> addVar(arr);
                    ASTNode* info = (*((*iter) -> getChildren()))[1];
                    VarPair size = VarPair(TEMP, temp_count++);
                    VarPair width = VarPair(TEMP, temp_count++);
                    VarPair space = VarPair(TEMP, temp_count++);
                    (this -> list).push_back(InterCode(VarPair(ARGTYPE::ARG_CONSTANT, atoi((info -> name).c_str())), DOP_ASSIGNMENT, size));
                    (this -> list).push_back(InterCode(VarPair(ARGTYPE::ARG_CONSTANT, 4), DOP_ASSIGNMENT, width));
                    (this -> list).push_back(InterCode(width, size, DOP_MULIPLY, space));
                    (this -> list).push_back(InterCode(space, ARRAY_DECLARATION, arr));
                }
                else if ((*iter) -> msg == "Initializer")
                {
                    ASTNode* var = (*((*iter) -> getChildren()))[0];
                    ASTNode* value = (*((*iter) -> getChildren()))[1];
                    if (var -> msg == "Var Declaration")
                    {
                        if (value -> msg == "Const Declaration")
                        {
                            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, atoi((value -> name).c_str()));
                            VarPair temp = VarPair(TEMP, temp_count++);
                            VarPair variable = VarPair(VAR, var_count++, var -> name);
                            (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, temp));
                            vlist -> addVar(variable);
                            (this -> list).push_back(InterCode(temp, DOP_ASSIGNMENT, variable));
                        }
                        else if (value -> msg == "ID Declaration")
                        {
                            VarPair id = vlist -> findVar(value -> name);
                            if (id.type == NULL_ARG)
                            {
                                printf("%s\n", (value -> name).c_str());
                                printf("error: var not defined.\n");
                                // error: variable undefined
                            }
                            else
                            {
                                VarPair variable = VarPair(VAR, var_count++, (*iter) -> name);
                                vlist -> addVar(variable);
                                (this -> list).push_back(InterCode(id, DOP_ASSIGNMENT, variable));
                            }
                        }
                        else
                        {
                            VarPair temp_result = VarPair(TEMP, temp_count++);
                            this -> arithmetic(value, vlist, temp_result);
                            VarPair variable = VarPair(VAR, var_count++, var -> name);
                            vlist -> addVar(variable);
                            (this -> list).push_back(InterCode(temp_result, DOP_ASSIGNMENT, variable));
                            // error: fatal assignment
                        }
                    }
                    else if(var -> msg == "Arr Declaration")
                    {

                        // to be completed
                    }
                }
            }
        }
        // else if( )           // to be completed
        // {

        // }
    }
    else if (root -> msg == "Assignment Expression")
    {
        ASTNode* left = (*(root -> getChildren()))[0];
        ASTNode* right = (*(root -> getChildren()))[1];
        if (left -> msg == "ID Declaration")
        {
            VarPair var = vlist -> findVar(left -> name);
            if (var.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                // error: variable undefined
            }
            else
            {
                VarPair right_value = VarPair(TEMP, temp_count++); 
                this -> arithmetic(right, vlist, right_value);
                (this -> list).push_back(InterCode(right_value, DOP_ASSIGNMENT, var));
            }
        }
        else if (left -> msg == "Expr")
        {
            VarPair right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
            // do something
        }
        else
        {
            // error: xxx can't be a left value
        }
        
    }
    else if (root -> msg == "Selection Statement") {}
    else if (root -> msg == "Repeat Statement") {}
    else if (root -> msg == "Input Expression") {}
    else if (root -> msg == "Output Expression") {}
    else if (root -> msg == "Jump Statement") {}
    else if (root -> msg == "") {}
    // to be completed
};

void InterCodeList::printCodeList()
{
    printf("printcodelist\n");
    for (auto iter = (this -> list).begin(); iter != (this -> list).end(); iter ++)
    {
        printf("%s", (*iter).printCode().c_str());
    }
    // to be completed
};
