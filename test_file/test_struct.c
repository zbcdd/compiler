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

int a = 2;
int k[5];

int main()
{
    struct struct_a a;
    struct struct_b b;
    a.b = 2;
    int c;
    c = 3 * (5 + a.b);
    return 0;
}


