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
    while(a + b) {
        cout << a;
    }
    if (a + b) {
        cout << a;
    } else if (a == 3) {
        cout << b;
    } else {
        cout << c;
    }

    if (a == b) {
        a = a + 1;
        cin >> a >> b;
        cout << a;
        cout << b << c;
        a = a + b;
    }

    if (1) a = a + 1;

    if (a == b) cout << b;
    else if (a == c) cout << b;
    else cout << c << d << e;
    int i;
    for (i = 0; i < 10; i = i + 1) {
        cout << a;
    }

    for (; ; ) {
        cout << a;
    }
    for (; i < 10; i = i + 1) {
        cout << a;
    }
    for (; ; i = i + 1) {
        cout << a;
    }
    
    for (i = 0; i < 10; i = i + 1);

    for (i = 0; i < 10;)
        a = a + 1;

    return 0;
}