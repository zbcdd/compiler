/*
测试连续的同级运算符产生的bug
*/
int a = 1, b = 2, c = 3, d = 4;
int main()
{
    a = a + b + c;
    a = a - b - c;
    a = a + b - c;
    a = a * b * c;
    a = a / b / c;
    a = a * b / c;
    a = a / b * c % d;
    a = a ^ b ^ c;
    if (a == b && c == d && b == c) {
        a = 3;
    } else if (a == b || c == d && a == b || b == c || c == d) {
        b = 4;
    } else {
        c = 5;
    }
    return 0;
}