struct A
{
    int a;
    int b;
};
int a = 0;

int main() {
    int a = 1, b = 2, ee[20], ff[30];
    int c = 2;
    int i = 0;
    c = a * b ^ c;
    for (i = 0; i < 10; i = i + 1) {
        int a;
        if (a<5) a = a + 1;
        else if (a>=5) {
            int a;
            a = a + 2;
        }
    }
    // 或者是其他自定义的输出函数
    cout << i;
    while (a < 40) {
        int a;
        a = a + 1;
    }
    cout << a;
    return 0;
}
