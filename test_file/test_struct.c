struct struct_a {
    int a;
    int b;
    int c;
};

struct struct_b {
    int b, c;
    int a;
} d;

struct {
    int a, b;
} c;

int main()
{
    struct struct_a a;
    struct struct_b b;
    
    return 0;
}


